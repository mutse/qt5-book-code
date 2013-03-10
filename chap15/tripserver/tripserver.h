#ifndef TRIPSERVER_H
#define TRIPSERVER_H

#include <QTcpServer>

class TripServer : public QTcpServer
{
    Q_OBJECT

public:
    TripServer(QObject *parent = 0);

private:
    void incomingConnection(int socketId);
};

#endif
