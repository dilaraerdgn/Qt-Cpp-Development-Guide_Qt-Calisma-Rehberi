#ifndef ETIKET_H
#define ETIKET_H

#include <QLabel>
#include <QDropEvent>
#include <QDragEnterEvent>

class etiket : public QLabel
{
    Q_OBJECT
public:
    explicit etiket(QWidget *parent = nullptr);

private:
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

signals:
};

#endif // ETIKET_H
