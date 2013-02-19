#include <QtWidgets>

#include "projectdialog.h"

ProjectDialog::ProjectDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    projectA->addItem("Giosue Carducci");
    projectA->addItem("Eyvind Johnson");
    projectA->addItem("Sally Prudhomme");
    projectA->addItem("Henryk Sienkiewicz");
    projectA->addItem("Carl Spitteler");
    projectA->addItem("Rabindranath Tagore");
    projectA->addItem("Kawabata Yasunari");

    projectB->addItem("Rudolf Eucken");
    projectB->addItem("Anatole France");
    projectB->addItem("Rudyard Kipling");
    projectB->addItem("Thomas Mann");
    projectB->addItem("Eugene O'Neill");
    projectB->addItem("Sigrid Undset");
}

void ProjectDialog::on_leftButton_clicked()
{
    moveCurrentItem(projectB, projectA);
}

void ProjectDialog::on_rightButton_clicked()
{
    moveCurrentItem(projectA, projectB);
}

void ProjectDialog::moveCurrentItem(ProjectListWidget *source,
                                    ProjectListWidget *target)
{
    if (source->currentItem()) {
        QListWidgetItem *newItem = source->currentItem()->clone();
        target->addItem(newItem);
        target->setCurrentItem(newItem);
        delete source->currentItem();
    }
}
