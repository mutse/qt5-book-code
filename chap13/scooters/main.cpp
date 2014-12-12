#include <QtWidgets>
#include <QtSql>

#include "scooterwindow.h"

bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL"); // QSQLITE
    db.setDatabaseName("scooters.dat");
    if (!db.open()) {
        QMessageBox::warning(0, QObject::tr("Database Error"),
                             db.lastError().text());
        return false;
    }
    return true;
}

void createFakeData()
{
    QSqlQuery query;
    query.exec("DROP TABLE scooter");

    query.exec("CREATE TABLE scooter ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "name VARCHAR(40) NOT NULL, "
               "maxspeed INTEGER NOT NULL, "
               "maxrange INTEGER NOT NULL, "
               "weight INTEGER NOT NULL, "
               "description VARCHAR(80) NOT NULL)");
    query.exec("INSERT INTO scooter (name, maxspeed, "
               "maxrange, weight, description) "
               "VALUES ('Mod-Rad 1500', 40, 35, 298, "
               "'Speedometer, odometer, battery meter, turn signal "
               "indicator, locking steering column')");
    query.exec("INSERT INTO scooter (name, maxspeed, "
               "maxrange, weight, description) "
               "VALUES ('Rad2Go Great White E36', 22, 12, 93, "
               "'10\" airless tires')");
    query.exec("INSERT INTO scooter (name, maxspeed, "
               "maxrange, weight, description) "
               "VALUES ('X-Treme X360', 21, 14, 59, "
               "'Cargo rack, foldable')");
    query.exec("INSERT INTO scooter (name, maxspeed, "
               "maxrange, weight, description) "
               "VALUES ('Vego SX 600', 20, , 76, "
               "'Two interchangeable batteries, foldable')");
    query.exec("INSERT INTO scooter (name, maxspeed, "
               "maxrange, weight, description) "
               "VALUES ('Sunbird E Bike', 18, 30, 118, '')");
    query.exec("INSERT INTO scooter (name, maxspeed, "
               "maxrange, weight, description) "
               "VALUES ('Leopard Shark', 16, 12, 63, "
               "'Battery indicator, removable seat, foldable')");
    query.exec("INSERT INTO scooter (name, maxspeed, "
               "maxrange, weight, description) "
               "VALUES ('Vego iQ 450', 15, 0, 60, "
               "'OUT OF STOCK')");
    query.exec("INSERT INTO scooter (name, maxspeed, "
               "maxrange, weight, description) "
               "VALUES ('X-Treme X-11', 15, 11, 38, "
               "'High powered brakes, foldable')");
    query.exec("INSERT INTO scooter (name, maxspeed, "
               "maxrange, weight, description) "
               "VALUES ('ZZ Cruiser', 14, 10, 46, "
               "'Two batteries, removable seat')");
    query.exec("INSERT INTO scooter (name, maxspeed, "
               "maxrange, weight, description) "
               "VALUES ('X-Treme X-010', 10, 10, 14, "
               "'Solid tires')");
    query.exec("INSERT INTO scooter (name, maxspeed, "
               "maxrange, weight, description) "
               "VALUES ('Q Electric Chariot', 10, 15, 60, "
               "'Foldable')");
    query.exec("INSERT INTO scooter (name, maxspeed, "
               "maxrange, weight, description) "
               "VALUES ('X-Treme X250', 15, 12, 0, "
               "'Solid aluminum deck')");
    query.exec("INSERT INTO scooter (name, maxspeed, "
               "maxrange, weight, description) "
               "VALUES ('Go MotorBoard 2000X', 15, 0, 20, "
               "'Foldable and carryable')");
    query.exec("INSERT INTO scooter (name, maxspeed, "
               "maxrange, weight, description) "
               "VALUES ('Goped ESR750 Sport Electric Scooter', "
               "20, 6, 45, " "'Foldable and carryable')");
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    bool create = !QFile::exists("scooters.dat");

	ScooterWindow window;
	window.resize(600, 500);
    window.show();

    if (!createConnection())
        return 1;
    if (create)
        createFakeData();

    return app.exec();
}
