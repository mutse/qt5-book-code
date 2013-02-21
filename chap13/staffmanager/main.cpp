#include <QtWidgets>
#include <QtSql>
#include <cstdlib>

#include "mainform.h"

bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL"); // QSQLITE
    db.setDatabaseName("personnel.dat");
    if (!db.open()) {
        QMessageBox::warning(0, QObject::tr("Database Error"),
                             db.lastError().text());
        return false;
    }
    return true;
}

void createFakeData()
{
    QStringList names;
    names << "Eabha Biddell" << "Prentice Hutchison"
          << "Rameesha Davidge" << "Digby Roson" << "Nettah Newarch"
          << "Lewisha Middleton" << "Ahmed Hanmer"
          << "Jordyn-Leigh Lamant" << "Lindsay Bigham"
          << "Kaylay Weir" << "Sofia Weir" << "Coel Spurlock"
          << "Youcef Culpan" << "Lucy-Jasmine Blanchard"
          << "Ally Hodgkin" << "Ara Collinge" << "Luka Dempster"
          << "Samanta Winster" << "Keri Palin" << "Ruiridh Bisset"
          << "Norman Epworth" << "Kezia Raw"
          << "Kaylan-Thomas Swynford" << "Kashaf Benning"
          << "Norma Yair" << "Edan Bassett" << "Akshat Mcglasson"
          << "Philippa Upton" << "Tylor Rockliff" << "Aqdas Buckman"
          << "Briana Dowell" << "Querida North" << "Chelsay Botts"
          << "Kishanth Calloway" << "Jan Covington"
          << "Teighan Monson" << "Claudia Mendel" << "Kerra Doe"
          << "Kara Depp" << "Harlie Soole" << "Viggo Streeter"
          << "Ava Cofel" << "Catherine Balderston"
          << "Brendan Gosnay" << "Zhaoyun Haygarth" << "Deri Pepler"
          << "Vicki Hopwood" << "Amitra Bindless" << "Cerhys Hayton"
          << "Gwendoline Westall";

    QProgressDialog progress;
    progress.setWindowModality(Qt::WindowModal);
    progress.setWindowTitle(QObject::tr("Staff Manager"));
    progress.setLabelText(QObject::tr("Creating database..."));
    progress.setMinimum(0);
    progress.setMaximum(names.count() + 6);
    progress.setValue(1);
    qApp->processEvents();
    QSqlQuery query;
    query.exec("DROP TABLE department");
    query.exec("DROP TABLE employee");
    query.exec("DROP TABLE location");

    progress.setValue(2);
    qApp->processEvents();
    query.exec("CREATE TABLE location ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "name VARCHAR(40) NOT NULL)");
    progress.setValue(3);
    qApp->processEvents();
    query.exec("CREATE TABLE department ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "name VARCHAR(40) NOT NULL, "
               "locationid INTEGER NOT NULL, "
               "FOREIGN KEY (locationid) REFERENCES location)");
    progress.setValue(4);
    qApp->processEvents();
    query.exec("CREATE TABLE employee ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "name VARCHAR(40) NOT NULL, "
               "departmentid INTEGER NOT NULL, "
               "extension INTEGER NOT NULL, "
               "email VARCHAR(40) NOT NULL, "
               "startdate DATE NOT NULL, "
               "FOREIGN KEY (departmentid) REFERENCES department)");

    progress.setValue(5);
    qApp->processEvents();
    query.exec("INSERT INTO location (name) VALUES ("
               "'Floor 18, 1129 Evanston Heights, New York, NY')");
    query.exec("INSERT INTO location (name) VALUES ("
               "'The Shed, Elmtree Drive, Boston, MA')");
    query.exec("INSERT INTO location (name) VALUES ("
               "'14 Valentine Buildings, Amor Street, Cambridge, MA')");
    query.exec("INSERT INTO location (name) VALUES ("
               "'Bunker Building, Silo Avenue, Los Angeles, CA')");
    query.exec("INSERT INTO department (name, locationid) VALUES ("
               "'Sales', 1)");
    query.exec("INSERT INTO department (name, locationid) VALUES ("
               "'Marketing', 2)");
    query.exec("INSERT INTO department (name, locationid) VALUES ("
               "'Processing', 1)");
    query.exec("INSERT INTO department (name, locationid) VALUES ("
               "'Support', 4)");
    query.exec("INSERT INTO department (name, locationid) VALUES ("
               "'Research', 3)");

    progress.setValue(6);
    qApp->processEvents();
    int count = 0;
    query.prepare("INSERT INTO employee (name, departmentid, "
                  "extension, email, startdate) "
                  "VALUES (:name, :departmentid, :extension, "
                  ":email, :startdate)");
    foreach (QString name, names) {
        query.bindValue(":name", name);
        query.bindValue(":departmentid", 1 + (std::rand() % 5));
        query.bindValue(":extension", 400 + (std::rand() % 100));
        query.bindValue(":email", name.toLower().replace(" ", ".") +
                                  "@company.com");
        query.bindValue(":startdate",
                QDate::currentDate().addDays(-(std::rand() % 3600)));
        query.exec();
        ++count;
        progress.setValue(count + 6);
    }
    progress.setValue(progress.maximum());
    qApp->processEvents();
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    bool existingData = QFile::exists("personnel.dat");
    if (!createConnection())
        return 1;
    if (!existingData)
        createFakeData();

    MainForm form;
    form.resize(500, 600);
    form.show();
    return app.exec();
}
