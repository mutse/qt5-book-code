#ifndef CITYSCAPE_H
#define CITYSCAPE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class CityView;
QT_END_NAMESPACE

class Cityscape : public QMainWindow
{
    Q_OBJECT

public:
    Cityscape();

private:
    void generateCityBlocks();

    QGraphicsScene *scene;
    CityView *view;
};

#endif
