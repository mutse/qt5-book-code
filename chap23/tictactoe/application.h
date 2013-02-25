#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>

QT_BEGIN_NAMESPACE
class TicTacToe;
QT_END_NAMESPACE

class Application : public QApplication
{
    Q_OBJECT

public:
    Application(int &argc, char *argv[]);

    void setTicTacToe(TicTacToe *toe);
    void saveState(QSessionManager &sessionManager);
    void commitData(QSessionManager &sessionManager);

private:
    TicTacToe *ticTacToe;
};

#endif
