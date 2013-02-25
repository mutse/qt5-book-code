#include <QtWidgets>

#include "tictactoe.h"

TicTacToe::TicTacToe(QWidget *parent)
    : QWidget(parent)
{
    clearBoard();
    if (qApp->isSessionRestored())
        restoreState();

    setWindowTitle(tr("Tic-Tac-Toe"));
}

QSize TicTacToe::sizeHint() const
{
    return QSize(200, 200);
}

void TicTacToe::clearBoard()
{
    for (int row = 0; row < 3; ++row) {
        for (int column = 0; column < 3; ++column) {
            board[row][column] = Empty;
        }
    }
    turnNumber = 0;
}

void TicTacToe::restoreState()
{
    QFile file(sessionFileName());
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        for (int row = 0; row < 3; ++row) {
            for (int column = 0; column < 3; ++column) {
                in >> board[row][column];
                if (board[row][column] != Empty)
                    ++turnNumber;
            }
        }
    }
    update();
}

QString TicTacToe::sessionFileName() const
{
    return QDir::homePath() + "/.tictactoe_" + qApp->sessionId() + "_"
           + qApp->sessionKey();
}

QString TicTacToe::saveState() const
{
    QFile file(sessionFileName());
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        for (int row = 0; row < 3; ++row) {
            for (int column = 0; column < 3; ++column)
                out << board[row][column];
        }
    }
    return file.fileName();
}

bool TicTacToe::gameInProgress() const
{
    return turnNumber > 0 && turnNumber < 9;
}

void TicTacToe::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(QPen(Qt::red, 1.0));
    painter.drawLine(cellWidth(), 0, cellWidth(), height());
    painter.drawLine(2 * cellWidth(), 0, 2 * cellWidth(), height());
    painter.drawLine(0, cellHeight(), width(), cellHeight());
    painter.drawLine(0, 2 * cellHeight(), width(), 2 * cellHeight());

    painter.setPen(QPen(Qt::blue, 4.0));
    for (int row = 0; row < 3; ++row) {
        for (int column = 0; column < 3; ++column) {
            QRect r = cellRect(row, column);
            if (board[row][column] == Cross) {
                painter.drawLine(r.topLeft(), r.bottomRight());
                painter.drawLine(r.topRight(), r.bottomLeft());
            } else if (board[row][column] == Nought) {
                painter.drawEllipse(r);
            }
        }
    }

    painter.setPen(QPen(Qt::darkGreen, 3.0));
    for (int row = 0; row < 3; ++row) {
        if (threeInARow(row, 0, row, 2)) {
            int y = cellRect(row, 0).center().y();
            painter.drawLine(0, y, width(), y);
            turnNumber = 9;
        }
    }
    for (int column = 0; column < 3; ++column) {
        if (threeInARow(0, column, 2, column)) {
            int x = cellRect(0, column).center().x();
            painter.drawLine(x, 0, x, height());
            turnNumber = 9;
        }
    }
    if (threeInARow(0, 0, 2, 2)) {
        painter.drawLine(0, 0, width(), height());
        turnNumber = 9;
    }
    if (threeInARow(0, 2, 2, 0)) {
        painter.drawLine(0, height(), width(), 0);
        turnNumber = 9;
    }
}

void TicTacToe::mousePressEvent(QMouseEvent *event)
{
    if (turnNumber == 9) {
        clearBoard();
        update();
    } else {
        for (int row = 0; row < 3; ++row) {
            for (int column = 0; column < 3; ++column) {
                QRect r = cellRect(row, column);
                if (r.contains(event->pos())) {
                    if (board[row][column] == Empty) {
                        if (turnNumber % 2 == 0) {
                            board[row][column] = Cross;
                        } else {
                            board[row][column] = Nought;
                        }
                        ++turnNumber;
                        update();
                    }
                    break;
                }
            }
        }
    }
}

QRect TicTacToe::cellRect(int row, int column) const
{
    const int HMargin = width() / 20;
    const int VMargin = height() / 20;
    return QRect(column * cellWidth() + HMargin,
                 row * cellHeight() + VMargin,
                 cellWidth() - 2 * HMargin,
                 cellHeight() - 2 * VMargin);
}

bool TicTacToe::threeInARow(int row1, int column1, int row3,
                            int column3) const
{
    int row2 = (row1 + row3) / 2;
    int column2 = (column1 + column3) / 2;

    return board[row1][column1] != Empty
           && board[row2][column2] == board[row1][column1]
           && board[row3][column3] == board[row1][column1];
}
