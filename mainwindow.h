#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include "piedra.h"
#include "tijeras.h"
#include "papel.h"
#include "jugador.h"
#include <QGraphicsView>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startButton_clicked();
    void on_addPiedraButton_clicked();
    void on_addTijerasButton_clicked();
    void on_addPapelButton_clicked();
    void on_addJugadorButton_clicked();
    void updateGame();
    void spawnObjects();
    void updateCountdown();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QTimer *timer;
    QTimer *spawnTimer;
    QTimer *countdownTimer;
    int countdownTime;
    int puntajePiedra;
    int puntajeTijeras;
    int puntajePapel;
    int puntajeJugador;
    QList<Piedra*> piedras;
    QList<Tijeras*> tijeras;
    QList<Papel*> papeles;
    Jugador *jugador;
    bool jugadorActivo;

    void checkCollisions();
};

#endif // MAINWINDOW_H
