#ifndef WEATHERSTATION_H
#define WEATHERSTATION_H

#include <QDialog>
#include <QUdpSocket>

class QLabel;
class QLineEdit;

class WeatherStation : public QDialog
{
    Q_OBJECT

public:
    WeatherStation(QWidget *parent = 0);

private slots:
    void processPendingDatagrams();

private:
    QUdpSocket udpSocket;

    QLabel *dateLabel;
    QLabel *timeLabel;
    QLabel *temperatureLabel;
    QLabel *humidityLabel;
    QLabel *altitudeLabel;
    QLineEdit *dateLineEdit;
    QLineEdit *timeLineEdit;
    QLineEdit *temperatureLineEdit;
    QLineEdit *humidityLineEdit;
    QLineEdit *altitudeLineEdit;
};

#endif
