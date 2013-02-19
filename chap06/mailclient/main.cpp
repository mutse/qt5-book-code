#include <QApplication>

#include "mailclient.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MailClient client;
    client.show();
    return app.exec();
}
