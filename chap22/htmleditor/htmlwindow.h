#ifndef HTMLWINDOW_H
#define HTMLWINDOW_H

#include <QMainWindow>
#include <QScriptEngine>

QT_BEGIN_NAMESPACE
class QAction;
class QDir;
class QMenu;
class QTextEdit;
class HtmlSyntaxHighlighter;
QT_END_NAMESPACE

class HtmlWindow : public QMainWindow
{
    Q_OBJECT

public:
    HtmlWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void open();
    bool save();
    bool saveAs();
    void scriptActionTriggered();
    void about();
    void documentWasModified();

private:
    static QDir directoryOf(const QString &subdir);
    void createActions();
    void createMenus();
    void createScriptsMenu();
    bool okToContinue();
    bool loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);
    bool createScriptAction(const QString &jsFileName);

    QTextEdit *textEdit;
    HtmlSyntaxHighlighter *syntaxHighlighter;
    QScriptEngine interpreter;
    QString curFile;
    QString fileFilters;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *scriptsMenu;
    QMenu *helpMenu;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *exitAction;
    QAction *cutAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *aboutAction;
    QAction *aboutQtAction;
};

#endif
