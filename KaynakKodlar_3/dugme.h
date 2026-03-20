#ifndef DUGME_H
#define DUGME_H

#include <QPushButton>
#include <QTimer>

class MainWindow;
class dugme : public QPushButton
{
    Q_OBJECT
public:
    explicit dugme(MainWindow *form, QWidget *parent = nullptr);

private slots:
    void hareketlendir();
    void durdur();

signals:

private:
    QTimer *zamanlayici;
    bool durum;
};

#endif // DUGME_H
