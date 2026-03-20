#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "etiket.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int X = 100;
    int Y = 50;
    for (int i = 0; i < 2; ++i) {
        for (int k = 0; k < 3; ++k) {
            etiket *et = new etiket(this);
            et->setGeometry(X, Y, 150, 150);
            X += 160;
        }
        X = 100;
        Y += 160;
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
