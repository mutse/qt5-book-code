#include <QtWidgets>
#include <QtUiTools>

#include "htmlsyntaxhighlighter.h"
#include "htmlwindow.h"

Q_DECLARE_METATYPE(QScriptValue)

HtmlWindow::HtmlWindow()
{
    interpreter.setProcessEventsInterval(100);

    textEdit = new QTextEdit;
    textEdit->setLineWrapMode(QTextEdit::NoWrap);
    setCentralWidget(textEdit);

    syntaxHighlighter = new HtmlSyntaxHighlighter(textEdit->document());

    fileFilters = tr("HTML files (*.html)\n"
                     "XHTML files (*.xhtml)\n"
                     "All files (*)");

    createActions();
    createMenus();

    statusBar()->showMessage(tr("Ready"), 2000);

    connect(textEdit->document(), SIGNAL(contentsChanged()),
            this, SLOT(documentWasModified()));

    setCurrentFile("");
    resize(500, 400);
}

void HtmlWindow::closeEvent(QCloseEvent *event)
{
    if (okToContinue()) {
        event->accept();
    } else {
        event->ignore();
    }
}

void HtmlWindow::open()
{
    if (okToContinue()) {
        QString fileName =
                QFileDialog::getOpenFileName(this, tr("Open"), ".",
                                             fileFilters);
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}

bool HtmlWindow::save()
{
    if (curFile.isEmpty()) {
        return saveAs();
    } else {
        saveFile(curFile);
        return true;
    }
}

bool HtmlWindow::saveAs()
{
    QString fileName =
            QFileDialog::getSaveFileName(this, tr("Save As"), curFile,
                                         fileFilters);
    if (QFile::exists(fileName)) {
        int r = QMessageBox::warning(this, tr("HTML Editor"),
                        tr("File %1 already exists.\n"
                           "Do you want to overwrite it?")
                        .arg(QDir::toNativeSeparators(fileName)),
                        QMessageBox::Yes | QMessageBox::No);
        if (r == QMessageBox::No)
            return true;
    }
    if (!fileName.isEmpty())
        saveFile(fileName);
    return true;
}

void HtmlWindow::scriptActionTriggered()
{
    QAction *action = qobject_cast<QAction *>(sender());
    QScriptValue qsScript = action->data().value<QScriptValue>();
    qsScript.property("run").call(qsScript);
}

void HtmlWindow::about()
{
    QMessageBox::about(this, tr("About HTML Editor"),
            tr("<h2>HTML Editor 1.1</h2>"
               "<p>Copyright &copy; 2008 Software Inc."
               "<p>HTML Editor is a small application that "
               "demonstrates how to extend a Qt/C++ application using "
               "ECMAScript and <i>Qt Designer</i> <tt>.ui</tt> files. "
               "The Scripts menu is constructed at run-time based on "
               "contents of the <tt>scripts</tt> subdirectory."));
}

void HtmlWindow::documentWasModified()
{
    setWindowModified(true);
}

QDir HtmlWindow::directoryOf(const QString &subdir)
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

void HtmlWindow::createActions()
{
    openAction = new QAction(tr("&Open..."), this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing HTML document"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save the HTML document to disk"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAction = new QAction(tr("Save &As..."), this);
    saveAsAction->setStatusTip(tr("Save the HTML document under a new "
                                  "name"));
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    cutAction = new QAction(tr("Cu&t"), this);
    cutAction->setIcon(QIcon(":/images/cut.png"));
    cutAction->setShortcut(QKeySequence::Cut);
    cutAction->setStatusTip(tr("Cut the current selection to the "
                               "clipboard"));
    connect(cutAction, SIGNAL(triggered()), textEdit, SLOT(cut()));

    copyAction = new QAction(tr("&Copy"), this);
    copyAction->setIcon(QIcon(":/images/copy.png"));
    copyAction->setShortcut(QKeySequence::Copy);
    copyAction->setStatusTip(tr("Copy the current selection to the "
                                "clipboard"));
    connect(copyAction, SIGNAL(triggered()), textEdit, SLOT(copy()));

    pasteAction = new QAction(tr("&Paste"), this);
    pasteAction->setIcon(QIcon(":/images/paste.png"));
    pasteAction->setShortcut(QKeySequence::Paste);
    pasteAction->setStatusTip(tr("Paste the clipboard's contents at "
                                 "the cursor position"));
    connect(pasteAction, SIGNAL(triggered()), textEdit, SLOT(paste()));

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("Show the application's About box"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void HtmlWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);

    createScriptsMenu();

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
}

void HtmlWindow::createScriptsMenu()
{
    scriptsMenu = menuBar()->addMenu(tr("&Scripts"));

    QDir scriptsDir = directoryOf("scripts");
    QStringList jsFileNames = scriptsDir.entryList(QStringList("*.js"),
                                                   QDir::Files);
    foreach (QString jsFileName, jsFileNames)
        createScriptAction(scriptsDir.absoluteFilePath(jsFileName));

    scriptsMenu->setEnabled(!scriptsMenu->isEmpty());
}

bool HtmlWindow::okToContinue()
{
    if (isWindowModified()) {
        int r = QMessageBox::warning(this, tr("HTML Editor"),
                        tr("The document has been modified.\n"
                           "Do you want to save your changes?"),
                        QMessageBox::Yes | QMessageBox::No
                        | QMessageBox::Cancel);
        if (r == QMessageBox::Yes) {
            return save();
        } else if (r == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

bool HtmlWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("HTML Editor"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(strippedName(fileName))
                             .arg(file.errorString()));
        statusBar()->showMessage(tr("Loading canceled"), 2000);
        return false;
    }

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    textEdit->setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
    return true;
}

bool HtmlWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("HTML Editor"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(strippedName(fileName))
                             .arg(file.errorString()));
        statusBar()->showMessage(tr("Saving canceled"), 2000);
        return false;
    }

    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << textEdit->toPlainText();
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void HtmlWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    setWindowModified(false);

    QString shownName = tr("Untitled");
    if (!curFile.isEmpty())
        shownName = strippedName(curFile);

    setWindowTitle(tr("%1[*] - %2").arg(shownName)
                                   .arg(tr("HTML Editor")));
}

QString HtmlWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

bool HtmlWindow::createScriptAction(const QString &jsFileName)
{
    QFile jsFile(jsFileName);
    if (!jsFile.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("HTML Editor"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(strippedName(jsFileName))
                             .arg(jsFile.errorString()));
        return false;
    }

    QTextStream in(&jsFile);
    in.setCodec("UTF-8");
    QString script = in.readAll();
    jsFile.close();

    QScriptValue qsScript = interpreter.evaluate(script);
    if (interpreter.hasUncaughtException()) {
        QMessageBox messageBox(this);
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.setWindowTitle(tr("HTML Editor"));
        messageBox.setText(tr("An error occurred while executing the "
                              "script %1.")
                           .arg(strippedName(jsFileName)));
        messageBox.setInformativeText(
                tr("%1.").arg(interpreter.uncaughtException()
                              .toString()));
        messageBox.setDetailedText(
                interpreter.uncaughtExceptionBacktrace().join("\n"));
        messageBox.exec();
        return false;
    }

    QString uiFileName = jsFileName;
    uiFileName.chop(3);
    uiFileName += ".ui";

    QFile uiFile(uiFileName);
    if (!uiFile.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("HTML Editor"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(strippedName(uiFileName))
                             .arg(uiFile.errorString()));
        return false;
    }

    QUiLoader loader;
    QWidget *dialog = loader.load(&uiFile, this);
    uiFile.close();
    if (!dialog) {
        QMessageBox::warning(this, tr("HTML Editor"),
                             tr("Error loading %1.")
                             .arg(strippedName(uiFileName)));
        return false;
    }

    QScriptValue qsDialog = interpreter.newQObject(dialog);
    qsScript.setProperty("dialog", qsDialog);

    QScriptValue qsTextEdit = interpreter.newQObject(textEdit);
    qsScript.setProperty("textEdit", qsTextEdit);

    QAction *action = new QAction(this);
    action->setText(qsScript.property("text").toString());
    action->setData(QVariant::fromValue(qsScript));
    connect(action, SIGNAL(triggered()),
            this, SLOT(scriptActionTriggered()));

    scriptsMenu->addAction(action);

    return true;
}
