#include <QtWidgets>

#include "cursorhandler.h"

CursorHandler::CursorHandler()
{
    state = BeforeHeader;
    currentImageNo = 0;
    numImages = 0;
}

bool CursorHandler::canRead() const
{
    if (state == BeforeHeader) {
        return device()->peek(4) == QByteArray("\0\0\2\0", 4);
    } else {
        return state != Error;
    }
}

bool CursorHandler::read(QImage *image)
{
    readHeaderIfNecessary();

    if (state != BeforeImage)
        return false;

    quint32 size;
    quint32 width;
    quint32 height;
    quint16 numPlanes;
    quint16 bitsPerPixel;
    quint32 compression;

    QDataStream in(device());
    in.setByteOrder(QDataStream::LittleEndian);
    in >> size;
    if (size != 40) {
        enterErrorState();
        return false;
    }
    in >> width >> height >> numPlanes >> bitsPerPixel >> compression;
    height /= 2;

    if (numPlanes != 1 || bitsPerPixel != 1 || compression != 0) {
        enterErrorState();
        return false;
    }

    in.skipRawData((size - 20) + 8);

    QBitArray xorBitmap = readBitmap(width, height, in);
    QBitArray andBitmap = readBitmap(width, height, in);

    if (in.status() != QDataStream::Ok) {
        enterErrorState();
        return false;
    }

    *image = QImage(width, height, QImage::Format_ARGB32);

    for (int i = 0; i < int(height); ++i) {
        for (int j = 0; j < int(width); ++j) {
            QRgb color;
            int bit = (i * width) + j;

            if (andBitmap.testBit(bit)) {
                if (xorBitmap.testBit(bit)) {
                    color = 0x7F7F7F7F;
                } else {
                    color = 0x00FFFFFF;
                }
            } else {
                if (xorBitmap.testBit(bit)) {
                    color = 0xFFFFFFFF;
                } else {
                    color = 0xFF000000;
                }
            }
            image->setPixel(j, i, color);
        }
    }

    ++currentImageNo;
    if (currentImageNo == numImages)
        state = AfterLastImage;
    return true;
}

bool CursorHandler::jumpToNextImage()
{
    QImage image;
    return read(&image);
}

int CursorHandler::currentImageNumber() const
{
    return currentImageNo;
}

int CursorHandler::imageCount() const
{
    readHeaderIfNecessary();
    return numImages;
}

void CursorHandler::readHeaderIfNecessary() const
{
    if (state != BeforeHeader)
        return;

    quint16 reserved;
    quint16 type;
    quint16 count;

    QDataStream in(device());
    in.setByteOrder(QDataStream::LittleEndian);

    in >> reserved >> type >> count;
    in.skipRawData(16 * count);

    if (in.status() != QDataStream::Ok || reserved != 0
            || type != 2 || count == 0) {
        enterErrorState();
        return;
    }

    state = BeforeImage;
    currentImageNo = 0;
    numImages = int(count);
}

QBitArray CursorHandler::readBitmap(int width, int height,
                                    QDataStream &in) const
{
    QBitArray bitmap(width * height);
    quint32 word = 0;
    quint8 byte;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if ((j % 32) == 0) {
                word = 0;
                for (int k = 0; k < 4; ++k) {
                    in >> byte;
                    word = (word << 8) | byte;
                }
            }

            bitmap.setBit(((height - i - 1) * width) + j,
                          word & 0x80000000);
            word <<= 1;
        }
    }
    return bitmap;
}

void CursorHandler::enterErrorState() const
{
    state = Error;
    currentImageNo = 0;
    numImages = 0;
}
