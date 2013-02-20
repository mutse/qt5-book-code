#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QDialog>
#include <QList>

QT_BEGIN_NAMESPACE
class QDir;
class QLineEdit;
class QToolButton;
QT_END_NAMESPACE

class Calculator : public QDialog
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = 0);

private slots:
    void digitClicked();
    void unaryOperatorClicked();
    void additiveOperatorClicked();
    void multiplicativeOperatorClicked();
    void equalClicked();
    void pointClicked();
    void changeSignClicked();
    void backspaceClicked();
    void customButtonClicked();
    void clear();
    void clearAll();
    void clearMemory();
    void readMemory();
    void setMemory();
    void addToMemory();

private:
    static QDir directoryOf(const QString &subdir);
    void createCustomButtons();
    QToolButton *createButton(const QString &text, const char *member);
    void abortOperation();
    void setDisplayValue(double value);
    bool calculate(double rightOperand, const QString &pendingOperator);

    double sumInMemory;
    double sumSoFar;
    double factorSoFar;
    QString pendingAdditiveOperator;
    QString pendingMultiplicativeOperator;
    bool waitingForOperand;

    QLineEdit *display;

    enum { NumDigitButtons = 10 };
    QToolButton *digitButtons[NumDigitButtons];
    QToolButton *pointButton;
    QToolButton *changeSignButton;
    QToolButton *backspaceButton;
    QToolButton *clearButton;
    QToolButton *clearAllButton;
    QToolButton *clearMemoryButton;
    QToolButton *readMemoryButton;
    QToolButton *setMemoryButton;
    QToolButton *addToMemoryButton;
    QToolButton *divisionButton;
    QToolButton *timesButton;
    QToolButton *minusButton;
    QToolButton *plusButton;
    QToolButton *squareRootButton;
    QToolButton *powerButton;
    QToolButton *reciprocalButton;
    QToolButton *equalButton;
    QList<QToolButton *> customButtons;
};

#endif
