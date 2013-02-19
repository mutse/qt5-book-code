#include <QtWidgets>

#include "node.h"
#include "propertiesdialog.h"

PropertiesDialog::PropertiesDialog(Node *node, QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    this->node = node;
    xSpinBox->setValue(int(node->x()));
    ySpinBox->setValue(int(node->y()));
    textLineEdit->setText(node->text());
    textColor = node->textColor();
    outlineColor = node->outlineColor();
    backgroundColor = node->backgroundColor();

    updateColorLabel(outlineColorLabel, outlineColor);
    updateColorLabel(backgroundColorLabel, backgroundColor);
    updateColorLabel(textColorLabel, textColor);
}

void PropertiesDialog::on_buttonBox_accepted()
{
    node->setPos(xSpinBox->value(), ySpinBox->value());
    node->setText(textLineEdit->text());
    node->setOutlineColor(outlineColor);
    node->setBackgroundColor(backgroundColor);
    node->setTextColor(textColor);
    node->update();
    QDialog::accept();
}

void PropertiesDialog::on_textColorButton_clicked()
{
    chooseColor(textColorLabel, &textColor);
}

void PropertiesDialog::on_outlineColorButton_clicked()
{
    chooseColor(outlineColorLabel, &outlineColor);
}

void PropertiesDialog::on_backgroundColorButton_clicked()
{
    chooseColor(backgroundColorLabel, &backgroundColor);
}

void PropertiesDialog::updateColorLabel(QLabel *label,
                                        const QColor &color)
{
    QPixmap pixmap(16, 16);
    pixmap.fill(color);
    label->setPixmap(pixmap);
}

void PropertiesDialog::chooseColor(QLabel *label, QColor *color)
{
    QColor newColor = QColorDialog::getColor(*color, this);
    if (newColor.isValid()) {
        *color = newColor;
        updateColorLabel(label, *color);
    }
}
