#include "rundialog.h"
#include "ui_rundialog.h"
#include <iostream>

RunDialog::RunDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RunDialog)
{
    ui->setupUi(this);
}

RunDialog::~RunDialog()
{
    delete ui;
}

void RunDialog::printMess(QString str ){
    QTextStream out(&str);
     str = ui->textEdit->toPlainText();
    out << str;

}
