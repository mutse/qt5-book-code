TEMPLATE      = lib
TARGET = cursorplugin
QT += widgets
CONFIG       += plugin
HEADERS       = cursorhandler.h \
                cursorplugin.h
SOURCES       = cursorhandler.cpp \
                cursorplugin.cpp
DESTDIR       = ./imageformats  #$$[QT_INSTALL_PLUGINS]/imageformats

EXAMPLE_FIFLES += cursorplugin.json
