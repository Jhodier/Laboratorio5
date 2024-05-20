#include "piedra.h"

Piedra::Piedra(QObject *parent)
    : QObject(parent), QGraphicsItem()
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Piedra::moveDown);
    timer->start(1000 / 33); // ~30 FPS

    stripe = new QPixmap(":/imagenes/piedra.png"); // Asegúrate de usar la ruta correcta a tu imagen
    rowPixmap = 0;
    colpixmap = 0;
    width = stripe->width();
    height = stripe->height();
    speed = 5; // Ajusta la velocidad según sea necesario
}

QRectF Piedra::boundingRect() const
{
    return QRectF(0, 0, width, height);
}

void Piedra::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawPixmap(0, 0, *stripe, colpixmap, rowPixmap, width, height);
}

void Piedra::moveDown()
{
    setPos(x(), y() + speed);
    if (y() > scene()->height()) {
        setPos(x(), -height); // Reiniciar posición en la parte superior
    }
}
void Piedra::setPosition(bool top)
{
    qreal x = qreal(rand() % int(scene()->width()));
    qreal y = top ? qreal(-height) : qreal(scene()->height());
    setPos(x, y);
}
