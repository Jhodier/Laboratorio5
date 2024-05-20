#include "tijeras.h"

Tijeras::Tijeras(QObject *parent)
    : QObject(parent), QGraphicsItem()
{
    stripe = new QPixmap(":/imagenes/tijeras.png"); // Asegúrate de usar la ruta correcta a tu imagen
    width = stripe->width();
    height = stripe->height();
    rowPixmap = 0;
    colpixmap = 0;
    speed = 5; // Ajusta la velocidad según sea necesario

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Tijeras::moveLeft);
    timer->start(50); // El tiempo puede ser ajustado según las necesidades
}

QRectF Tijeras::boundingRect() const
{
    return QRectF(0, 0, width, height);
}

void Tijeras::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawPixmap(0, 0, *stripe, colpixmap, rowPixmap, width, height);
}

void Tijeras::moveLeft()
{
    setPos(x() - speed, y());
    if (x() + width < 0) {
        scene()->removeItem(this); // Eliminar cuando sale del área de la escena
        delete this;
    }
}

void Tijeras::setPosition(bool left)
{
    if (left) {
        setPos(-width, static_cast<qreal>(rand() % static_cast<int>(scene()->height()))); // Posicionar a la izquierda
    } else {
        setPos(static_cast<qreal>(scene()->width()), static_cast<qreal>(rand() % static_cast<int>(scene()->height()))); // Posicionar a la derecha
    }
}
