#ifndef PAPEL_H
#define PAPEL_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsScene>
class Papel : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    explicit Papel(QObject *parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void moveDiagonally();
    void setPosition(int corner);

private:
    QTimer* timer;
    QPixmap* stripe;
    qreal rowPixmap, colpixmap, width, height;
    int speedX;
    int speedY;
};

#endif // PAPEL_H
