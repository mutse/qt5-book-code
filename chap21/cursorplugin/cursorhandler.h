#ifndef CURIMAGEHANDLER_H
#define CURIMAGEHANDLER_H

#include <QImageIOHandler>

class CursorHandler : public QImageIOHandler
{
public:
    CursorHandler();

    bool canRead() const;
    bool read(QImage *image);
    bool jumpToNextImage();
    int currentImageNumber() const;
    int imageCount() const;

private:
    enum State { BeforeHeader, BeforeImage, AfterLastImage, Error };

    void readHeaderIfNecessary() const;
    QBitArray readBitmap(int width, int height, QDataStream &in) const;
    void enterErrorState() const;

    mutable State state;
    mutable int currentImageNo;
    mutable int numImages;
};

#endif
