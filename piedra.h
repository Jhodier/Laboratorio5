#ifndef PIEDRA_H
#define PIEDRA_H
#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>

class Piedra : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    explicit Piedra(QObject *parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void moveDown();
    void setPosition(bool top);

private:
    QTimer* timer;
    QPixmap* stripe;
    qreal rowPixmap, colpixmap, width, height;
    int speed;
};

#endif // PIEDRA_H
