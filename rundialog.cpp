#include "rundialog.h"
#include "ui_rundialog.h"
#include "Program/Program.h"
#include <iostream>

RunDialog::RunDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RunDialog)
{
    ui->setupUi(this);

    QString fileName = QFileDialog::getOpenFileName(this,
    tr("Open Program"), nullptr, tr("Compiled Files (*.json)"));

    Program* program = new Program(fileName.toStdString());
    program->moveToThread(&programThread);

    connect(&programThread, &QThread::finished, program, &QObject::deleteLater);
    connect(this, &RunDialog::execute, program, &Program::execute);
    connect(program, &Program::print, this, &RunDialog::printMess);
    connect(this, &RunDialog::input, program, &Program::input);


    programThread.start();
}

RunDialog::~RunDialog()
{
    programThread.quit();
    programThread.wait();
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
