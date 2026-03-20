#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
/*
    db.setHostName()
    db.setUserName()
    db.setPassword()
*/
    db.setDatabaseName("/home/users/okul.db");
    if (!db.open()) {
        QMessageBox::critical(this, "Bağlantı Hatası", db.lastError().text());
    }
    sorgu = new QSqlQuery(db);
    ekleme = new QSqlQuery(db);
    model = new QSqlQueryModel();
    listele();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::listele()
{
    sorgu->exec("select * from ogrenci");
    model->setQuery(*sorgu);
    ui->tableView->setModel(model);
}

void MainWindow::on_pushButton_clicked()
{
    ekleme->prepare("insert into ogrenci values(?, ?, ?, ?, ?)");
    ekleme->addBindValue(ui->numara->text());
    ekleme->addBindValue(ui->ad->text());
    ekleme->addBindValue(ui->soyad->text());
    ekleme->addBindValue(ui->tel->text());
    ekleme->addBindValue(ui->sinif->currentText());
    if (!ekleme->exec()) {
        QMessageBox::critical(this, "Bağlantı Hatası", ekleme->lastError().text());
    }
    listele();
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    num = model->index(index.row(), 0).data().toString();
    ui->numara->setText(num);
    ui->ad->setText(model->index(index.row(), 1).data().toString());
    ui->soyad->setText(model->index(index.row(), 2).data().toString());
    ui->tel->setText(model->index(index.row(), 3).data().toString());
    ui->sinif->setCurrentIndex(model->index(index.row(), 4).data().toInt() - 1);
}


void MainWindow::on_pushButton_2_clicked()
{
    ekleme->prepare("update ogrenci set numara = ?, adi = ?, soyadi = ?, telefon = ?, sinif = ? where numara = ?");
    ekleme->addBindValue(ui->numara->text());
    ekleme->addBindValue(ui->ad->text());
    ekleme->addBindValue(ui->soyad->text());
    ekleme->addBindValue(ui->tel->text());
    ekleme->addBindValue(ui->sinif->currentText());
    ekleme->addBindValue(num);
    if (!ekleme->exec()) {
        QMessageBox::critical(this, "Bağlantı Hatası", ekleme->lastError().text());
    }
    listele();
}

