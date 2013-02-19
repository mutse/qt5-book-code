#ifndef MAILCLIENT_H
#define MAILCLIENT_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QIcon;
class QSplitter;
class QTextEdit;
class QTreeWidget;
QT_END_NAMESPACE

class MailClient : public QMainWindow
{
    Q_OBJECT

public:
    MailClient();

protected:
    void closeEvent(QCloseEvent *event);

private:
    void addFolder(const QIcon &icon, const QString &name);
    void addMessage(const QString &subject, const QString &from,
                    const QString &date);
    void readSettings();
    void writeSettings();

    QSplitter *mainSplitter;
    QSplitter *rightSplitter;
    QTreeWidget *foldersTreeWidget;
    QTreeWidget *messagesTreeWidget;
    QTextEdit *textEdit;
};

#endif
