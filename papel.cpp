#include "papel.h"

Papel::Papel(QObject *parent)
    : QObject(parent), QGraphicsItem()
    , rowPixmap(0), colpixmap(0), width(50), height(50), speedX(2), speedY(2)
{
    timer = new QTimer(this);
    stripe = new QPixmap(":/imagenes/papel.png"); // Asegúrate de usar la ruta correcta a tu imagen
    connect(timer, &QTimer::timeout, this, &Papel::moveDiagonally);
    timer->start(100); // Actualizar cada 100 ms
}

QRectF Papel::boundingRect() const
{
    return QRectF(0, 0, width, height);
}

void Papel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(0, 0, *stripe, colpixmap, rowPixmap, width, height);
}

void Papel::moveDiagonally()
{
    colpixmap += speedX;
    rowPixmap += speedY;

    if (colpixmap + width > stripe->width() || colpixmap < 0) {
        speedX = -speedX;
    }
    if (rowPixmap + height > stripe->height() || rowPixmap < 0) {
        speedY = -speedY;
    }
}

void Papel::setPosition(int corner)
{
    switch (corner) {
        case 0: // Esquina superior izquierda
            setPos(0, 0);
            break;
        case 1: // Esquina superior derecha
            setPos(scene()->width() - width, 0);
            break;
        case 2: // Esquina inferior izquierda
            setPos(0, scene()->height() - height);
            break;
        case 3: // Esquina inferior derecha
            setPos(scene()->width() - width, scene()->height() - height);
            break;
    }
}
