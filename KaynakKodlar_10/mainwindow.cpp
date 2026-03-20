#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/users/okul.db");
    db.open();

    ogrenci = new QSqlQuery(db);
    dersler = new QSqlQuery(db);
    notlar = new QSqlQuery(db);
    genel = new QSqlQuery(db);
    combo = new QSqlQuery(db);
    ogrmodel = new QSqlQueryModel();
    dersmodel = new QSqlQueryModel();
    notmodel = new QSqlQueryModel();
    combomodel = new QSqlQueryModel();
    combo->exec("select distinct donemi from dersler");
    combomodel->setQuery(*combo);
    ui->comboBox->setModel(combomodel);
    ogrenciListele("");
    dersListele(ui->comboBox->currentText());

    printer = new QPrinter();
    dialog = new QPrintPreviewDialog(printer);
    connect(dialog, SIGNAL(paintRequested(QPrinter*)),this, SLOT(yazdir()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ogrenciListele(QString prm)
{
    if (prm.isEmpty()) {
        ogrenci->exec("select * from ogrenci");
    } else {
        ogrenci->exec("select * from ogrenci where adi like '" + prm + "%'");
    }
    ogrmodel->setQuery(*ogrenci);
    ui->ogrTable->setModel(ogrmodel);
}

void MainWindow::dersListele(QString dnm)
{
    dersler->prepare("SELECT * FROM dersler d where NOT EXISTS (SELECT 1 from notlar n where d.dersKodu = n.dersNo AND ogrno = ?) and donemi = ?");
    dersler->addBindValue(ogrno);
    dersler->addBindValue(dnm);
    dersler->exec();
    dersmodel->setQuery(*dersler);
    ui->dersTable->setModel(dersmodel);
}

void MainWindow::notListele(QString ogrencino)
{
    if (!ogrencino.isEmpty()) {
        notlar->prepare("select * from notlar where ogrno = ?");
        notlar->addBindValue(ogrencino);
        notlar->exec();
        notmodel->setQuery(*notlar);
        ui->notTable->setModel(notmodel);
    }
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    ogrenciListele(arg1);
}


void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    dersListele(arg1);
}


void MainWindow::on_ogrTable_clicked(const QModelIndex &index)
{
    ogrno = ogrmodel->index(index.row(), 0).data().toString();
    notListele(ogrno);
    dersListele(ui->comboBox->currentText());
}


void MainWindow::on_dersTable_clicked(const QModelIndex &index)
{
    dersno = dersmodel->index(index.row(), 0).data().toString();
}


void MainWindow::on_pushButton_clicked()
{
    genel->prepare("insert into notlar(ogrno, dersNo) values (?, ?)");
    genel->addBindValue(ogrno);
    genel->addBindValue(dersno);
    genel->exec();
    notListele(ogrno);
    dersListele(ui->comboBox->currentText());
}


void MainWindow::on_pushButton_2_clicked()
{
    dialog->exec();
}

void MainWindow::yazdir()
{
    QPainter painter(printer);
    painter.drawText(10, 10, "Numarası");
    painter.drawLine(10, 20, 80, 20);
    painter.drawText(100, 10, "Adı");
    painter.drawLine(100, 20, 180, 20);
    painter.drawText(200, 10, "Soyadı");
    painter.drawLine(200, 20, 280, 20);
    painter.drawText(300, 10, "Telefon");
    painter.drawLine(300, 20, 380, 20);
    painter.drawText(390, 10, "Sınıfı");
    painter.drawLine(390, 20, 470, 20);

    int Y = 50;
    for (int i = 0; i < ogrmodel->rowCount(); ++i) {
        painter.drawText(10, Y, ogrmodel->index(i, 0).data().toString());
        painter.drawText(100, Y, ogrmodel->index(i, 1).data().toString());
        painter.drawText(200, Y, ogrmodel->index(i, 2).data().toString());
        painter.drawText(300, Y, ogrmodel->index(i, 3).data().toString());
        painter.drawText(390, Y, ogrmodel->index(i, 4).data().toString());
        Y += 30;
    }

}

