#ifndef PROPERTIESDIALOG_H
#define PROPERTIESDIALOG_H

#include "ui_propertiesdialog.h"

QT_BEGIN_NAMESPACE
class Node;
QT_END_NAMESPACE

class PropertiesDialog : public QDialog, private Ui::PropertiesDialog
{
    Q_OBJECT

public:
    PropertiesDialog(Node *node, QWidget *parent = 0);

private slots:
    void on_buttonBox_accepted();
    void on_textColorButton_clicked();
    void on_outlineColorButton_clicked();
    void on_backgroundColorButton_clicked();

private:
    void updateColorLabel(QLabel *label, const QColor &color);
    void chooseColor(QLabel *label, QColor *color);

    Node *node;
    QColor textColor;
    QColor outlineColor;
    QColor backgroundColor;
};

#endif
