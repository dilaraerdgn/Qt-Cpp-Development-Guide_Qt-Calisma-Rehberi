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


void MainWindow::on_pushButton_2_clicked()
{
    QString sonuclar = "";
    if (ui->bay->isChecked()) {
        sonuclar += "Cinsiyeti Bay\n";
    } else {
        sonuclar += "Cinsiyeti Bayan\n";
    }
    if (ui->evli->isChecked()) {
        sonuclar += "Medeni Hali: Evli\n";
    } else if (ui->bekar->isChecked()){
        sonuclar += "Medeni Hali: Bekar\n";
    }
    else {
        sonuclar += "Medeni Hali: Dul\n";
    }
    if (ui->ev->isChecked()) {
        sonuclar += "Evi Var\n";
    }
    if (ui->araba->isChecked()) {
        sonuclar += "Arabası Var";
    }
    ui->label_4->setText(sonuclar);
}


void MainWindow::on_pushButton_3_pressed()
{
    ui->pushButton_3->setGeometry(ui->pushButton_3->x() -15,
                                  ui->pushButton_3->y() -15,
                                  60, 60);
}


void MainWindow::on_pushButton_3_released()
{
    ui->pushButton_3->setGeometry(ui->pushButton_3->x() + 15,
                                  ui->pushButton_3->y() + 15,
                                  30, 30);

}


void MainWindow::on_pushButton_4_clicked()
{
    if ((ui->pushButton_4->x() + ui->pushButton_4->width() + ui->horizontalSlider->value()) <= width() ) {

        ui->pushButton_4->setGeometry(ui->pushButton_4->x() + ui->horizontalSlider->value(),
                                  ui->pushButton_4->y(),
                                  ui->pushButton_4->width(),
                                  ui->pushButton_4->height());
    }
}


void MainWindow::on_pushButton_5_clicked()
{
    QImage resim(":/res/geri.png");
    ui->label_6->setPixmap(QPixmap::fromImage(resim));
}

