#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    /*
    QString isim;
    isim = ui->lineEdit->text();
    ui->label->setText(isim);
    */

    //ui->label->setText("Merhaba " + ui->lineEdit->text());
    /*
    int sayi1, sayi2, sonuc;

    sayi1 = ui->lineEdit->text().toInt();
    sayi2 = ui->lineEdit_2->text().toInt();
    sonuc = sayi1 + sayi2;
    ui->label->setText(QString::number(sonuc));
*/
    ui->label->setText(QString::number(ui->lineEdit->text().toInt() + ui->lineEdit_2->text().toInt()));
}

