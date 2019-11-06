#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include "Program/Program.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionCreate_New_triggered();

    void on_actionOpen_triggered();
    
    void on_actionSave_triggered();
    
    void on_actionCopy_triggered();
    
    void on_actionPaste_triggered();
      
    void on_actionUndo_triggered();

    void on_actionExit_triggered();

    void on_actionRedo_triggered();



    void on_actionSave_As_triggered();

    void on_actionCompile_triggered();

private:
    Ui::MainWindow *ui;
    QString currentFile = "";
};

#endif // MAINWINDOW_H
