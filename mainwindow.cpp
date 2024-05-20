#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , jugador(nullptr)
    , jugadorActivo(false)
    , puntajePiedra(0)
    , puntajeTijeras(0)
    , puntajePapel(0)
    , puntajeJugador(0)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateGame);

    spawnTimer = new QTimer(this);
    connect(spawnTimer, &QTimer::timeout, this, &MainWindow::spawnObjects);

    countdownTimer = new QTimer(this);
    connect(countdownTimer, &QTimer::timeout, this, &MainWindow::updateCountdown);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    timer->start(16); // Aproximadamente 60 FPS
}

void MainWindow::on_addPiedraButton_clicked()
{
    if (piedras.size() < 5) {
        Piedra *piedra = new Piedra(this);
        bool top = qrand() % 2 == 0;
        piedra->setPosition(top);
        piedras.append(piedra);
        scene->addItem(piedra);
    }
}

void MainWindow::on_addTijerasButton_clicked()
{
    if (tijeras.size() < 5) {
        Tijeras *tijera = new Tijeras(this);
        bool left = qrand() % 2 == 0;
        tijera->setPosition(left);
        tijeras.append(tijera);
        scene->addItem(tijera);
    }
}

void MainWindow::on_addPapelButton_clicked()
{
    if (papeles.size() < 5) {
        Papel *papel = new Papel(this);
        int corner = qrand() % 4;
        papel->setPosition(corner);
        papeles.append(papel);
        scene->addItem(papel);
    }
}


void MainWindow::on_addJugadorButton_clicked()
{
    if (!jugadorActivo) {
        jugador = new Jugador(this);
        jugador->setPos(scene->width() / 2, scene->height() / 2);
        scene->addItem(jugador);
        jugadorActivo = true;
        countdownTime = 300; // 5 minutes countdown
        countdownTimer->start(1000); // 1-second intervals

        // Disable buttons
        ui->addPiedraButton->setEnabled(false);
        ui->addTijerasButton->setEnabled(false);
        ui->addPapelButton->setEnabled(false);
        ui->addJugadorButton->setEnabled(false);

        spawnTimer->start(10000); // Create objects every 10 seconds
    }
}

void MainWindow::updateGame()
{
    for (Piedra *piedra : qAsConst(piedras)) {
        piedra->moveDown();
    }
    for (Tijeras *tijera : qAsConst(tijeras)) {
        tijera->moveLeft();
    }
    for (Papel *papel : qAsConst(papeles)) {
        papel->moveDiagonally();
    }
    if (jugadorActivo) {
        // Implement this method in the Jugador class
        jugador->move();
    }

    // Check collisions and update scores
    checkCollisions();
}

void MainWindow::spawnObjects()
{
    if (piedras.size() < 5) on_addPiedraButton_clicked();
    if (tijeras.size() < 5) on_addTijerasButton_clicked();
    if (papeles.size() < 5) on_addPapelButton_clicked();
}

void MainWindow::updateCountdown()
{
    countdownTime--;
    ui->countdownLabel->setText(QString::number(countdownTime));
    if (countdownTime <= 0) {
        countdownTimer->stop();
        spawnTimer->stop();
        timer->stop();
        QMessageBox::information(this, "Fin de juego", "El juego ha terminado.");
        // Determine winner
        QString winner;
        if (puntajeJugador > puntajePiedra && puntajeJugador > puntajeTijeras && puntajeJugador > puntajePapel) {
            winner = "Jugador";
        } else if (puntajePiedra > puntajeTijeras && puntajePiedra > puntajePapel) {
            winner = "Piedras";
        } else if (puntajeTijeras > puntajePapel) {
            winner = "Tijeras";
        } else {
            winner = "Papeles";
        }
        QMessageBox::information(this, "Ganador", "El ganador es: " + winner);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (jugadorActivo) {
        switch (event->key()) {
            case Qt::Key_W:
                jugador->moveUp();
                break;
            case Qt::Key_S:
                jugador->moveDown();
                break;
            case Qt::Key_A:
                jugador->moveLeft();
                break;
            case Qt::Key_D:
                jugador->moveRight();
                break;
            case Qt::Key_Space:
                jugador->attack();
                break;
        }
    }
}

void MainWindow::checkCollisions()
{
    // Aquí se implementa la detección de colisiones y la lógica para destruir objetos
    // y actualizar los puntajes según las reglas de piedra, papel, tijeras.

    // Ejemplo de lógica de colisión:
    for (Piedra *piedra : qAsConst(piedras)) {
        for (Tijeras *tijera : qAsConst(tijeras)) {
            if (piedra->collidesWithItem(tijera)) {
                scene->removeItem(tijera);
                tijeras.removeOne(tijera);
                delete tijera;
                puntajePiedra++;
                break;
            }
        }
        for (Papel *papel : qAsConst(papeles)) {
            if (piedra->collidesWithItem(papel)) {
                scene->removeItem(piedra);
                piedras.removeOne(piedra);
                delete piedra;
                puntajePapel++;
                break;
            }
        }
    }

    for (Tijeras *tijera : qAsConst(tijeras)) {
        for (Papel *papel : qAsConst(papeles)) {
            if (tijera->collidesWithItem(papel)) {
                scene->removeItem(papel);
                papeles.removeOne(papel);
                delete papel;
                puntajeTijeras++;
                break;
            }
        }
    }

    // También se debe implementar la colisión con el jugador y actualizar puntajes.
}
