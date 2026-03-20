#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDragEnterEvent>

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

private slots:
    void on_action_A_triggered();

    void on_action_Kaydet_triggered();

    void on_action_Farkl_Kaydet_triggered();

    void on_action_leri_triggered();

    void on_action_Geri_triggered();

private:
    Ui::MainWindow *ui;
    void Ac(QString dosyaYolu);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    QString dosyaYoluGlobal;
};
#endif // MAINWINDOW_H
