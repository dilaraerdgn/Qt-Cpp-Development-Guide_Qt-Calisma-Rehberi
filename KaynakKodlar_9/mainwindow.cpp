#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLineEdit>
#include <QCheckBox>
#include <QSqlDatabase>
#include <QLabel>
#include <QMessageBox>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/users/okul.db");
    db.open();
    ders = new QSqlQuery(db);
    ogrenci = new QSqlQuery(db);
    guncelle = new QSqlQuery(db);
    dersModel = new QSqlQueryModel();
    ogrenciModel = new QSqlQueryModel();

    ders->exec("select dersKodu, adi from dersler");
    dersModel->setQuery(*ders);
    ui->comboBox->setModel(dersModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ogrenciListele(QString kod)
{
    ui->label->setText(kod);
    ogrenci->prepare("SELECT numara, adi, soyadi, vizesi from ogrenci inner join notlar  on ogrenci.numara = notlar.ogrno where dersNo = ?");
    ogrenci->addBindValue(kod);
    ogrenci->exec();
    ogrenciModel->setQuery(*ogrenci);
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(ogrenciModel->rowCount());
    QStringList baslik = {"Öğrenci No", "Adı", "Soyadı", "Vize Notu"};
    ui->tableWidget->setHorizontalHeaderLabels(baslik);
    //ui->label->setText(QString::number(ogrenciModel->rowCount()));
    for (int i = 0; i < ogrenciModel->rowCount(); ++i) {
        ui->tableWidget->setCellWidget(i, 0, new QLabel(ogrenciModel->index(i, 0).data().toString()));
        ui->tableWidget->setCellWidget(i, 1, new QLabel(ogrenciModel->index(i, 1).data().toString()));
        ui->tableWidget->setCellWidget(i, 2, new QLabel(ogrenciModel->index(i, 2).data().toString()));
        ui->tableWidget->setCellWidget(i, 3, new QLineEdit(ogrenciModel->index(i, 3).data().toString()));
    }
}

void MainWindow::on_pushButton_clicked()
{
    QLineEdit *ed;
    QLabel *no;
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        ed = (QLineEdit *) ui->tableWidget->cellWidget(i, 3);
        no = (QLabel *) ui->tableWidget->cellWidget(i, 0);
        guncelle->prepare("update notlar set vizesi = ? where ogrno = ? and dersNo = ?");
        guncelle->addBindValue(ed->text());
        guncelle->addBindValue(no->text());
        guncelle->addBindValue(ui->comboBox->currentText());
        if (!guncelle->exec()) {
            QMessageBox::critical(this, "Kayıt Hatası", guncelle->lastError().text());
        }
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    QString okunanlar = "";
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        QLineEdit *ed = (QLineEdit *) ui->tableWidget->cellWidget(i, 0);
        okunanlar += ed->text() + "\n";
    }
    ui->label->setText(okunanlar);
}


void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    ogrenciListele(arg1);
}

