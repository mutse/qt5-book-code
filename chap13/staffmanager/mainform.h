#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QLabel;
class QModelIndex;
class QPushButton;
class QSplitter;
class QSqlRelationalTableModel;
class QTableView;
QT_END_NAMESPACE

enum {
    Department_Id = 0,
    Department_Name = 1,
    Department_LocationId = 2
};

class MainForm : public QWidget
{
    Q_OBJECT

public:
    MainForm();

private slots:
    void updateEmployeeView();
    void addDepartment();
    void deleteDepartment();
    void editEmployees();

private:
    void createDepartmentPanel();
    void createEmployeePanel();

    QSqlRelationalTableModel *departmentModel;
    QSqlRelationalTableModel *employeeModel;
    QWidget *departmentPanel;
    QWidget *employeePanel;
    QLabel *departmentLabel;
    QLabel *employeeLabel;
    QTableView *departmentView;
    QTableView *employeeView;
    QSplitter *splitter;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *editButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;
};

#endif
