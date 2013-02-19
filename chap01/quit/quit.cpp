#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QPushButton *button = new QPushButton("Quit");

    QObject::connect(button, &QPushButton::clicked, &QApplication::quit);
 
    button->show();
    return app.exec();
}
