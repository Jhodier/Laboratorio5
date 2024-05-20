#include "jugador.h"

Jugador::Jugador(QObject *parent)
    : QObject(parent), QGraphicsItem()
{
    sprite = new QPixmap(":/imagenes/jugador.png"); // Ajusta la ruta de tu imagen
    width = sprite->width();
    height = sprite->height();
    posX = 0;
    posY = 0;
    speed = 5;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Jugador::actualizarEscena);
    timer->start(50); // Ajusta según sea necesario
}

QRectF Jugador::boundingRect() const
{
    return QRectF(0, 0, width, height);
}

void Jugador::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawPixmap(0, 0, *sprite, 0, 0, width, height);
}

void Jugador::move()
{
    // Lógica de movimiento
    setPos(posX, posY);
}

void Jugador::moveUp()
{
    posY -= speed;
    if (posY < 0) posY = 0;
}

void Jugador::moveDown()
{
    posY += speed;
    if (posY + height > scene()->height()) posY = scene()->height() - height;
}

void Jugador::moveLeft()
{
    posX -= speed;
    if (posX < 0) posX = 0;
}

void Jugador::moveRight()
{
    posX += speed;
    if (posX + width > scene()->width()) posX = scene()->width() - width;
}

void Jugador::attack()
{
    // Lógica de ataque
}

void Jugador::actualizarEscena()
{
    move();
    update();
}
