#include "etiket.h"
#include <QMimeData>
#include <QDrag>

etiket::etiket(QWidget *parent)
    : QLabel{parent}
{
    show();
    setScaledContents(true);
    setFrameShape(QFrame::Box);
    setAcceptDrops(true);
}

void etiket::dropEvent(QDropEvent *event)
{
    etiket *gelen = qobject_cast<etiket*>(event->source());
    if (gelen && gelen != this) {
        QPixmap birakilan(pixmap());
        setPixmap(gelen->pixmap());
        gelen->setPixmap(birakilan);
    } else if(gelen == this){
        return;
    } else {
        QList<QUrl> yollar = event->mimeData()->urls();
        QString yol = yollar.first().toLocalFile();
        if (!yol.isEmpty()) {
            setPixmap(QPixmap(yol));
        }
    }
}

void etiket::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();
}

void etiket::mouseMoveEvent(QMouseEvent *event)
{
    QMimeData *mdata= new QMimeData();
    mdata->setImageData(pixmap().toImage());
    QDrag *suruklenen = new QDrag(this);
    suruklenen->setMimeData(mdata);
    suruklenen->setPixmap(mdata->imageData().value<QPixmap>());
    suruklenen->exec(Qt::MoveAction);
}
