#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlQueryModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void ogrenciListele(QString prm);
    void dersListele(QString dnm);
    void notListele(QString ogrencino);

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_ogrTable_clicked(const QModelIndex &index);

    void on_dersTable_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QSqlQuery *ogrenci, *dersler, *notlar, *genel, *combo;
    QSqlQueryModel *ogrmodel, *dersmodel, *notmodel, *combomodel;
    QString ogrno, dersno;
};
#endif // MAINWINDOW_H
