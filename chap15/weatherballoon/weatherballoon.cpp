#include <QtCore>
#include <QtNetwork>
#include <cstdlib>

#include "weatherballoon.h"

WeatherBalloon::WeatherBalloon(QWidget *parent)
    : QPushButton(tr("Quit"), parent)
{
    connect(this, SIGNAL(clicked()), this, SLOT(close()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(sendDatagram()));

    timer.start(2 * 1000);

    setWindowTitle(tr("Weather Balloon"));
}

double WeatherBalloon::temperature() const
{
    return -20.0 + (2.0 * std::rand() / (RAND_MAX + 1.0));
}

double WeatherBalloon::humidity() const
{
    return 20.0 + (2.0 * std::rand() / (RAND_MAX + 1.0));
}

double WeatherBalloon::altitude() const
{
    return 7000 + (100.0 * std::rand() / (RAND_MAX + 1.0));
}

void WeatherBalloon::sendDatagram()
{
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_3);
    out << QDateTime::currentDateTime() << temperature() << humidity()
        << altitude();

    udpSocket.writeDatagram(datagram, QHostAddress::LocalHost, 5824);
}
