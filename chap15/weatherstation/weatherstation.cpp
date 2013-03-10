#include <QtWidgets>
#include <QtNetwork>

#include "weatherstation.h"

WeatherStation::WeatherStation(QWidget *parent)
    : QDialog(parent)
{
    udpSocket.bind(5824);

    connect(&udpSocket, SIGNAL(readyRead()),
            this, SLOT(processPendingDatagrams()));

    dateLabel = new QLabel(tr("Date:"));
    timeLabel = new QLabel(tr("Time:"));
    temperatureLabel = new QLabel(tr("Temperature:"));
    humidityLabel = new QLabel(tr("Humidity:"));
    altitudeLabel = new QLabel(tr("Altitude:"));

    dateLineEdit = new QLineEdit;
    timeLineEdit = new QLineEdit;
    temperatureLineEdit = new QLineEdit;
    humidityLineEdit = new QLineEdit;
    altitudeLineEdit = new QLineEdit;

    dateLineEdit->setReadOnly(true);
    timeLineEdit->setReadOnly(true);
    temperatureLineEdit->setReadOnly(true);
    humidityLineEdit->setReadOnly(true);
    altitudeLineEdit->setReadOnly(true);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(dateLabel, 0, 0);
    mainLayout->addWidget(dateLineEdit, 0, 1);
    mainLayout->addWidget(timeLabel, 1, 0);
    mainLayout->addWidget(timeLineEdit, 1, 1);
    mainLayout->addWidget(temperatureLabel, 2, 0);
    mainLayout->addWidget(temperatureLineEdit, 2, 1);
    mainLayout->addWidget(humidityLabel, 3, 0);
    mainLayout->addWidget(humidityLineEdit, 3, 1);
    mainLayout->addWidget(altitudeLabel, 4, 0);
    mainLayout->addWidget(altitudeLineEdit, 4, 1);
    setLayout(mainLayout);

    setWindowTitle(tr("Weather Station"));
}

void WeatherStation::processPendingDatagrams()
{
    QByteArray datagram;

    do {
        datagram.resize(udpSocket.pendingDatagramSize());
        udpSocket.readDatagram(datagram.data(), datagram.size());
    } while (udpSocket.hasPendingDatagrams());

    QDateTime dateTime;
    double temperature;
    double humidity;
    double altitude;

    QDataStream in(&datagram, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_4_3);
    in >> dateTime >> temperature >> humidity >> altitude;

    dateLineEdit->setText(dateTime.date().toString());
    timeLineEdit->setText(dateTime.time().toString());
    temperatureLineEdit->setText(tr("%1 C").arg(temperature));
    humidityLineEdit->setText(tr("%1%").arg(humidity));
    altitudeLineEdit->setText(tr("%1 m").arg(altitude));
}
