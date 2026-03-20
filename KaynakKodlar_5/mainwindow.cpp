#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QMimeData>

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

void MainWindow::on_action_A_triggered()
{
    QString yol = QFileDialog::getOpenFileName(this,"Text Dosya Aç","/home/users");
    if (!yol.isEmpty()) {
        dosyaYoluGlobal = yol;
        Ac(yol);
    }
}

void MainWindow::Ac(QString dosyaYolu)
{
    QFile dosya(dosyaYolu);
    if (dosya.open(QFile::ReadOnly)) {
        QTextStream okunacak(&dosya);
        QString okunan = okunacak.readAll();
        ui->textEdit->setText(okunan);
        dosya.close();
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();
}

void MainWindow::dropEvent(QDropEvent *event)
{
    QList<QUrl> yollar = event->mimeData()->urls();
    if (!yollar.isEmpty()) {
        QString isim = yollar.first().toLocalFile();
        dosyaYoluGlobal = isim;
        Ac(isim);
    }
}


void MainWindow::on_action_Kaydet_triggered()
{
    QFile dosya(dosyaYoluGlobal);
    if (dosya.open(QFile::WriteOnly)) {
        QTextStream yazilacak(&dosya);
        yazilacak << ui->textEdit->toPlainText();
        dosya.flush();
        dosya.close();
    }
}


void MainWindow::on_action_Farkl_Kaydet_triggered()
{
    QString test = QFileDialog::getSaveFileName(this,"Text Dosya Kaydet","/home/user");
    if (!test.isEmpty()) {
        dosyaYoluGlobal = test;
        on_action_Kaydet_triggered();
    }
}


void MainWindow::on_action_leri_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_action_Geri_triggered()
{
    ui->textEdit->undo();
}

