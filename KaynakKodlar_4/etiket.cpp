#include "etiket.h"
#include <QRandomGenerator>

etiket::etiket(QPoint konum, QWidget *parent)
    : QLabel{parent}
{
    show();
    setFrameShape(QFrame::Box);
    setGeometry(konum.x(), konum.y(), 100, 100);
    setScaledContents(true);
}

void etiket::mousePressEvent(QMouseEvent *ev)
{
    int resim = QRandomGenerator::global()->bounded(5);
    setPixmap(QPixmap(":/res/resimler/"+ QString::number(resim) +".png"));
    ilkKonum = ev->pos();
}

void etiket::mouseMoveEvent(QMouseEvent *ev)
{
    setGeometry(ev->pos().x() - ilkKonum.x()  + x(),
                ev->pos().y() - ilkKonum.y() + y(), width(), height());
}
