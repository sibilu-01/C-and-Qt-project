#ifndef RUNDIALOG_H
#define RUNDIALOG_H

#include <QDialog>
#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QThread>
#include <QEventLoop>

namespace Ui {
class RunDialog;
}

class RunDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::RunDialog *ui;

public:
    explicit RunDialog(QWidget *parent = nullptr);
    ~RunDialog() override;
    void showEvent(QShowEvent*) override;

private slots:

    void on_pushButton_pressed();

public slots:
    void printMess(QString);
signals:
    void execute();
    void input(QString);
};

#endif // RUNDIALOG_H
