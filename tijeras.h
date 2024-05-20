#ifndef TIJERAS_H
#define TIJERAS_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsScene>
class Tijeras : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    explicit Tijeras(QObject *parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void moveLeft();
    void setPosition(bool left);

private:
    QTimer* timer;
    QPixmap* stripe;
    qreal rowPixmap, colpixmap, width, height;
    int speed;
};

#endif // TIJERAS_H
