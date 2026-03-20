#include "dugme.h"
#include "mainwindow.h"

dugme::dugme(MainWindow *form, QWidget *parent)
    : QPushButton{parent}
{
    this->show();
    setGeometry(50,100, 30, 30);
    //connect(this, SIGNAL(clicked(bool)), form, SLOT(dugmeYoket()));
    connect(this, SIGNAL(clicked(bool)), this, SLOT(durdur()));
    zamanlayici = new QTimer();
    connect(zamanlayici, SIGNAL(timeout()), this, SLOT(hareketlendir()));
    zamanlayici->start(100);
    durum = true;
}

void dugme::hareketlendir()
{
    setGeometry(x() + 10, y(), width(), height());
}

void dugme::durdur()
{
    durum =!durum;
    if (durum) {
        zamanlayici->start(100);
    } else {
        zamanlayici->stop();
    }
}
