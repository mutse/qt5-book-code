TEMPLATE      = lib
TARGET = bronzestyleplugin
QT += widgets
CONFIG       += plugin
HEADERS       = ../bronze/bronzestyle.h \
                bronzestyleplugin.h
SOURCES       = ../bronze/bronzestyle.cpp \
                bronzestyleplugin.cpp
RESOURCES     = ../bronze/bronze.qrc
DESTDIR       = styles #$$[QT_INSTALL_PLUGINS]/styles
