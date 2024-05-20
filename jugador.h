#ifndef JUGADOR_H
#define JUGADOR_H
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPixmap>
#include <QTimer>
#include <QObject>
#include <QPainter>

class Jugador : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    explicit Jugador(QObject *parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void move();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void attack();

public slots:
    void actualizarEscena();

private:
    QTimer* timer;
    QPixmap* sprite;
    qreal posX, posY, width, height;
    int speed;
};

#endif // JUGADOR_H
