#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rundialog.h"
#include <QtConcurrent/QtConcurrent>
#include <QtConcurrent/QtConcurrentRun>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionCreate_New_triggered()
{
    currentFile.clear();
    ui->textEdit->setText((QString()));
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this , "Open File");
    QFile file(fileName);
    currentFile = fileName;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning", "File cannot be opened : " + file.errorString());
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_actionSave_triggered()
{

}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionExit_triggered()
{
   QApplication::quit();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
     ui->textEdit->paste();
}

void MainWindow::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save");
    QFile file(fileName);
    currentFile = fileName;
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot save file : " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void MainWindow::errorMessage(std::string str ){
    QMessageBox::warning(this, "Compile", QString::fromStdString(str));
}

void MainWindow::on_actionCompile_triggered()
{
    //Save the program
    QString fileName = QFileDialog::getSaveFileName(this, "Save");
    QFile file(fileName);
    currentFile = fileName;
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot save file : " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
    std::cout << fileName.toStdString() << std::endl;

    // Save path as string and pass into program

    Program* program = new Program(fileName.toStdString());
    std::string compiled = program->compile();
    errorMessage(compiled);
}

void MainWindow::on_actionRun_triggered()
{
        RunDialog runBox;
        runBox.setModal(true);

        QThread programThread;
        QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Program"), nullptr, tr("Compiled Files (*.json)"));

        Program* program = new Program(fileName.toStdString());
        program->moveToThread(&programThread);

        connect(&programThread, &QThread::finished, program, &QObject::deleteLater);
        connect(&runBox, &RunDialog::execute, program, &Program::execute);
        connect(program, &Program::print, &runBox, &RunDialog::printMess);
        connect(&runBox, &RunDialog::input, program, &Program::input);

        programThread.start();
        runBox.exec();

        programThread.quit();
        programThread.wait();
}

