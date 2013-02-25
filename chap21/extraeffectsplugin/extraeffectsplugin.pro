TEMPLATE      = lib
CONFIG       += plugin
TARGET		= extraeffectsplugin
QT += widgets
HEADERS       = ../textart/textartinterface.h \
                extraeffectsplugin.h
SOURCES       = extraeffectsplugin.cpp

DESTDIR       = ../textart/plugins

EXAMPLE_FILES += extraeffectsplugin.json
