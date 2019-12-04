#ifndef RUNDIALOG_H
#define RUNDIALOG_H

#include <QDialog>
#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <iostream>

namespace Ui {
class RunDialog;
}

class RunDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RunDialog(QWidget *parent = nullptr);
    ~RunDialog();

private slots:
void printMess(QString);



private:
    Ui::RunDialog *ui;
};

#endif // RUNDIALOG_H
