TEMPLATE      = app
TARGET = addressbook
QT           += widgets axserver
HEADERS       = abitem.h \
                addressbook.h \
                editdialog.h
SOURCES       = abitem.cpp \
                addressbook.cpp \
                editdialog.cpp \
                main.cpp
FORMS         = editdialog.ui
RC_FILE       = qaxserver.rc
