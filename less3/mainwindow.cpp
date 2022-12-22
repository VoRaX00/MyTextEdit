#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QDebug>
#include <QFileDialog>
#include <QIODevice>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDir dir("/Users");
    dir.setFilter(QDir::Files | QDir::Dirs | QDir::Hidden);
    QFileInfoList list = dir.entryInfoList();
    foreach(QFileInfo fileinfo, list){
        qDebug() << fileinfo.fileName();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(path=="")
    {
        path = QFileDialog::getSaveFileName();
        ok=true;
    }
    if(path.isEmpty())
    {
        return;
    }
    QFile file(path);
    if(file.open(QIODevice::WriteOnly)){
        QString text = ui->textEdit->toPlainText();
        QByteArray ba = text.toUtf8();
        file.write(ba, ba.length());
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    path = QFileDialog::getOpenFileName();
    if(path.isEmpty())
    {
        return;
    }

    QFile file(path);
    if(file.open(QIODevice::ReadOnly)){
        QByteArray ba = file.readAll();
        QString text(ba);
        ui->textEdit->setPlainText(text);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QFile file(":/ref/reference.txt");
    if(file.open(QIODevice::ReadOnly)){
        QByteArray ba = file.readAll();
        QString text(ba);
        QMessageBox box;
        box.setWindowTitle("Reference");
        box.setText(text);
        box.exec();
    }
}
