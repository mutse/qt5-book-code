#ifndef BRONZESTYLE_H
#define BRONZESTYLE_H

//#include <QWindowsStyle>
#include <QProxyStyle>

class BronzeStyle : public QProxyStyle
{
    Q_OBJECT

public:
    BronzeStyle() {}

    void polish(QPalette &palette);
    void polish(QWidget *widget);
    void unpolish(QWidget *widget);
    int styleHint(StyleHint which, const QStyleOption *option,
                  const QWidget *widget = 0,
                  QStyleHintReturn *returnData = 0) const;
    int pixelMetric(PixelMetric which, const QStyleOption *option,
                    const QWidget *widget = 0) const;
    void drawPrimitive(PrimitiveElement which,
                       const QStyleOption *option, QPainter *painter,
                       const QWidget *widget = 0) const;
    void drawComplexControl(ComplexControl which,
                            const QStyleOptionComplex *option,
                            QPainter *painter,
                            const QWidget *widget = 0) const;
    QRect subControlRect(ComplexControl whichControl,
                         const QStyleOptionComplex *option,
                         SubControl whichSubControl,
                         const QWidget *widget = 0) const;

public slots:
    QIcon standardIconImplementation(StandardPixmap which,
                                     const QStyleOption *option,
                                     const QWidget *widget = 0) const;

private:
    void drawBronzeFrame(const QStyleOption *option,
                         QPainter *painter) const;
    void drawBronzeBevel(const QStyleOption *option,
                         QPainter *painter) const;
    void drawBronzeCheckBoxIndicator(const QStyleOption *option,
                                     QPainter *painter) const;
    void drawBronzeSpinBoxButton(SubControl which,
                                 const QStyleOptionComplex *option,
                                 QPainter *painter) const;
};

#endif
