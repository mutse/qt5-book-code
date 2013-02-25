#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QAxWidget;
class QSlider;
class QToolButton;
QT_END_NAMESPACE

class PlayerWindow : public QWidget
{
    Q_OBJECT
    Q_ENUMS(ReadyStateConstants)

public:
    enum PlayStateConstants { Stopped = 0, Paused = 1, Playing = 2 };
    enum ReadyStateConstants { Uninitialized = 0, Loading = 1,
                               Interactive = 3, Complete = 4 };

    PlayerWindow();

protected:
    void timerEvent(QTimerEvent *event);

private slots:
    void onPlayStateChange(int oldState, int newState);
    void onReadyStateChange(ReadyStateConstants readyState);
    void onPositionChange(double oldPos, double newPos);
    void sliderValueChanged(int newValue);
    void openFile();

private:
    QAxWidget *wmp;
    QToolButton *openButton;
    QToolButton *playPauseButton;
    QToolButton *stopButton;
    QSlider *seekSlider;
    QString fileFilters;
    int updateTimer;
};

#endif
