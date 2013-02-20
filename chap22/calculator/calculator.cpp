#include <QtWidgets>
#include <QtScript>
#include <cmath>

#include "calculator.h"

Calculator::Calculator(QWidget *parent)
    : QDialog(parent)
{
    sumInMemory = 0.0;
    sumSoFar = 0.0;
    factorSoFar = 0.0;
    waitingForOperand = true;

    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);

    for (int i = 0; i < NumDigitButtons; ++i) {
        digitButtons[i] = createButton(QString::number(i),
                                       SLOT(digitClicked()));
    }

    pointButton = createButton(tr("."), SLOT(pointClicked()));
    changeSignButton = createButton(tr("\u00B1"), // \261
                                    SLOT(changeSignClicked()));

    backspaceButton = createButton(tr("Backspace"),
                                   SLOT(backspaceClicked()));
    clearButton = createButton(tr("Clear"), SLOT(clear()));
    clearAllButton = createButton(tr("Clear All"), SLOT(clearAll()));

    clearMemoryButton = createButton(tr("MC"), SLOT(clearMemory()));
    readMemoryButton = createButton(tr("MR"), SLOT(readMemory()));
    setMemoryButton = createButton(tr("MS"), SLOT(setMemory()));
    addToMemoryButton = createButton(tr("M+"), SLOT(addToMemory()));

    divisionButton = createButton(tr("\u00F7"), // \367
                             SLOT(multiplicativeOperatorClicked()));
    timesButton = createButton(tr("\u00D7"), // \327
                               SLOT(multiplicativeOperatorClicked()));
    minusButton = createButton(tr("-"),
                               SLOT(additiveOperatorClicked()));
    plusButton = createButton(tr("+"),
                              SLOT(additiveOperatorClicked()));

    squareRootButton = createButton(tr("Sqrt"),
                                    SLOT(unaryOperatorClicked()));
    powerButton = createButton(tr("x\u00B2"), // \262
                               SLOT(unaryOperatorClicked()));
    reciprocalButton = createButton(tr("1/x"),
                                    SLOT(unaryOperatorClicked()));
    equalButton = createButton(tr("="), SLOT(equalClicked()));

    createCustomButtons();

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setContentsMargins(8, 8, 8, 8);
    mainLayout->setHorizontalSpacing(5);
    mainLayout->setVerticalSpacing(5);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    mainLayout->addWidget(display, 0, 0, 1, 6);
    mainLayout->addWidget(backspaceButton, 1, 0, 1, 2);
    mainLayout->addWidget(clearButton, 1, 2, 1, 2);
    mainLayout->addWidget(clearAllButton, 1, 4, 1, 2);

    mainLayout->addWidget(clearMemoryButton, 2, 0);
    mainLayout->addWidget(readMemoryButton, 3, 0);
    mainLayout->addWidget(setMemoryButton, 4, 0);
    mainLayout->addWidget(addToMemoryButton, 5, 0);

    for (int i = 1; i < NumDigitButtons; ++i) {
        int row = ((9 - i) / 3) + 2;
        int column = ((i - 1) % 3) + 1;
        mainLayout->addWidget(digitButtons[i], row, column);
    }

    mainLayout->addWidget(digitButtons[0], 5, 1);
    mainLayout->addWidget(pointButton, 5, 2);
    mainLayout->addWidget(changeSignButton, 5, 3);

    mainLayout->addWidget(divisionButton, 2, 4);
    mainLayout->addWidget(timesButton, 3, 4);
    mainLayout->addWidget(minusButton, 4, 4);
    mainLayout->addWidget(plusButton, 5, 4);

    mainLayout->addWidget(squareRootButton, 2, 5);
    mainLayout->addWidget(powerButton, 3, 5);
    mainLayout->addWidget(reciprocalButton, 4, 5);
    mainLayout->addWidget(equalButton, 5, 5);

    for (int i = 0; i < customButtons.count(); ++i) {
        int row = 6 + (i / 3);
        int column = 2 * (i % 3);
        mainLayout->addWidget(customButtons[i], row, column, 1, 2);
    }

    setLayout(mainLayout);

    setWindowTitle(tr("Calculator"));
    setBackgroundRole(QPalette::Dark);
    setAutoFillBackground(true);
}

void Calculator::digitClicked()
{
    QToolButton *clickedButton = qobject_cast<QToolButton *>(sender());
    int digitValue = clickedButton->text().toInt();
    if (display->text() == "0" && digitValue == 0.0)
        return;

    if (waitingForOperand) {
        display->clear();
        waitingForOperand = false;
    }
    display->setText(display->text() + QString::number(digitValue));
}

void Calculator::unaryOperatorClicked()
{
    QToolButton *clickedButton = qobject_cast<QToolButton *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();
    double result = 0.0;

    if (clickedOperator == tr("Sqrt")) {
        if (operand < 0.0) {
            abortOperation();
            return;
        }
        result = std::sqrt(operand);
    } else if (clickedOperator == tr("x\u00B2")) { //\262
        result = std::pow(operand, 2.0);
    } else if (clickedOperator == tr("1/x")) {
        if (operand == 0.0) {
            abortOperation();
            return;
        }
        result = 1.0 / operand;
    }
    setDisplayValue(result);
    waitingForOperand = true;
}

void Calculator::additiveOperatorClicked()
{
    QToolButton *clickedButton = qobject_cast<QToolButton *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        setDisplayValue(factorSoFar);
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }

    if (!pendingAdditiveOperator.isEmpty()) {
        if (!calculate(operand, pendingAdditiveOperator)) {
            abortOperation();
            return;
        }
        setDisplayValue(sumSoFar);
    } else {
        sumSoFar = operand;
    }

    pendingAdditiveOperator = clickedOperator;
    waitingForOperand = true;
}

void Calculator::multiplicativeOperatorClicked()
{
    QToolButton *clickedButton = qobject_cast<QToolButton *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        setDisplayValue(factorSoFar);
    } else {
        factorSoFar = operand;
    }

    pendingMultiplicativeOperator = clickedOperator;
    waitingForOperand = true;
}

void Calculator::equalClicked()
{
    double operand = display->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }
    if (!pendingAdditiveOperator.isEmpty()) {
        if (!calculate(operand, pendingAdditiveOperator)) {
            abortOperation();
            return;
        }
        pendingAdditiveOperator.clear();
    } else {
        sumSoFar = operand;
    }

    setDisplayValue(sumSoFar);
    sumSoFar = 0.0;
    waitingForOperand = true;
}

void Calculator::pointClicked()
{
    if (waitingForOperand)
        display->setText("0");
    if (!display->text().contains("."))
        display->setText(display->text() + tr("."));
    waitingForOperand = false;
}

void Calculator::changeSignClicked()
{
    QString text = display->text();
    double value = text.toDouble();

    if (value > 0.0) {
        text.prepend(tr("-"));
    } else if (value < 0.0) {
        text.remove(0, 1);
    }
    display->setText(text);
}

void Calculator::backspaceClicked()
{
    if (waitingForOperand)
        return;

    QString text = display->text();
    text.chop(1);
    if (text.isEmpty()) {
        text = "0";
        waitingForOperand = true;
    }
    display->setText(text);
}

void Calculator::customButtonClicked()
{
    QToolButton *clickedButton = qobject_cast<QToolButton *>(sender());
    QFile file(clickedButton->property("scriptFileName").toString());
    if (!file.open(QIODevice::ReadOnly)) {
        abortOperation();
        return;
    }

    QTextStream in(&file);
    in.setCodec("UTF-8");
    QString script = in.readAll();
    file.close();

    QScriptEngine interpreter;
    QScriptValue operand(&interpreter, display->text().toDouble());
    interpreter.globalObject().setProperty("x", operand);
    QScriptValue result = interpreter.evaluate(script);
    if (!result.isNumber()) {
        abortOperation();
        return;
    }

    setDisplayValue(result.toNumber());
    waitingForOperand = true;
}

void Calculator::clear()
{
    display->setText("0");
    waitingForOperand = true;
}

void Calculator::clearAll()
{
    sumSoFar = 0.0;
    factorSoFar = 0.0;
    pendingAdditiveOperator.clear();
    pendingMultiplicativeOperator.clear();
    display->setText("0");
    waitingForOperand = true;
}

void Calculator::clearMemory()
{
    sumInMemory = 0.0;
}

void Calculator::readMemory()
{
    setDisplayValue(sumInMemory);
    waitingForOperand = true;
}

void Calculator::setMemory()
{
    equalClicked();
    sumInMemory = display->text().toDouble();
}

void Calculator::addToMemory()
{
    equalClicked();
    sumInMemory += display->text().toDouble();
}

QDir Calculator::directoryOf(const QString &subdir)
{
    QDir dir(QApplication::applicationDirPath());

#if defined(Q_OS_WIN)
    if (dir.dirName().toLower() == "debug"
            || dir.dirName().toLower() == "release")
        dir.cdUp();
#elif defined(Q_OS_MAC)
    if (dir.dirName() == "MacOS") {
        dir.cdUp();
        dir.cdUp();
        dir.cdUp();
    }
#endif
    dir.cd(subdir);
    return dir;
}

void Calculator::createCustomButtons()
{
    QDir scriptsDir = directoryOf("scripts");
    QStringList fileNames = scriptsDir.entryList(QStringList("*.js"),
                                                 QDir::Files);
    foreach (QString fileName, fileNames) {
        QString text = fileName;
        text.chop(3);
        QToolButton *button = createButton(text,
                                           SLOT(customButtonClicked()));
        button->setStyleSheet("color: rgb(31, 63, 127)");
        button->setProperty("scriptFileName",
                            scriptsDir.absoluteFilePath(fileName));
        customButtons.append(button);
    }
}

QToolButton *Calculator::createButton(const QString &text,
                                      const char *member)
{
    QToolButton *button = new QToolButton;
    button->setText(text);
    button->setSizePolicy(QSizePolicy::Expanding,
                          QSizePolicy::Preferred);

    int side = button->minimumSizeHint().height() + 14;
    button->setMinimumSize(side, side);

    connect(button, SIGNAL(clicked()), this, member);

    return button;
}

void Calculator::abortOperation()
{
    clearAll();
    display->setText(tr("####"));
}

void Calculator::setDisplayValue(double value)
{
    display->setText(QString::number(value, 'g', 15));
}

bool Calculator::calculate(double rightOperand,
                           const QString &pendingOperator)
{
    if (pendingOperator == tr("+")) {
        sumSoFar += rightOperand;
    } else if (pendingOperator == tr("-")) {
        sumSoFar -= rightOperand;
    } else if (pendingOperator == tr("\u00D7")) { // \327
        factorSoFar *= rightOperand;
    } else if (pendingOperator == tr("\u00F7")) { // \367
        if (rightOperand == 0.0)
            return false;
        factorSoFar /= rightOperand;
    }
    return true;
}
