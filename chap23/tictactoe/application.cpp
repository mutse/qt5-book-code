#include <QtWidgets>

#include "application.h"
#include "tictactoe.h"

Application::Application(int &argc, char *argv[])
    : QApplication(argc, argv)
{
    ticTacToe = 0;
}

void Application::setTicTacToe(TicTacToe *toe)
{
    ticTacToe = toe;
}

void Application::saveState(QSessionManager &sessionManager)
{
    QString fileName = ticTacToe->saveState();

    QStringList discardCommand;
    discardCommand << "rm" << fileName;
    sessionManager.setDiscardCommand(discardCommand);
}

void Application::commitData(QSessionManager &sessionManager)
{
    if (ticTacToe->gameInProgress()
            && sessionManager.allowsInteraction()) {
        int r = QMessageBox::warning(ticTacToe, tr("Tic-Tac-Toe"),
                        tr("The game hasn't finished.\n"
                           "Do you really want to quit?"),
                        QMessageBox::Yes | QMessageBox::No);
        if (r == QMessageBox::Yes) {
            sessionManager.release();
        } else {
            sessionManager.cancel();
        }
    }
}
