#ifndef ETIKET_H
#define ETIKET_H

#include <QLabel>
#include <QMouseEvent>

class etiket : public QLabel
{
    Q_OBJECT
public:
    explicit etiket(QPoint konum, QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);

private:
    QPoint ilkKonum;

signals:
};

#endif // ETIKET_H
