#include "rundialog.h"
#include "ui_rundialog.h"
#include "Program/Program.h"
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

void RunDialog::showEvent(QShowEvent *event) {
    emit execute();
}

void RunDialog::printMess(QString str) {
    QString output = str;
    output.replace("\\n", "\n");

    ui->plainTextEdit->insertPlainText(output);
}

void RunDialog::on_pushButton_pressed()
{
    emit input(ui->lineEdit->text());
    ui->lineEdit->setText("");
}
