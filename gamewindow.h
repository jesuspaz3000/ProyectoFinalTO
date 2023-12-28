#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include "player.h"
#include "gameobject.h"
#include <QList>
#include "fish.h"
#include "trash.h"
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include "infofish.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

class GameWindow : public QMainWindow {
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);  // Constructor
    ~GameWindow();  // Destructor
    void pauseGame();  // Pausa el juego deteniendo todos los temporizadores
    void resumeGame();  // Reanuda el juego iniciando todos los temporizadores

public slots:
    void spawnFish();  // Genera un pez
    void handleFishOutOfScreen(Fish *fish);  // Maneja peces fuera de pantalla
    void spawnTrash();  // Genera basura
    void handleTrashOutOfScreen(Trash *trash);  // Maneja basura fuera de pantalla
    void handleObjectCollision(GameObject* object, bool isColliding);  // Maneja las colisiones entre el jugador y otros objetos
    void updateScore();  // Actualiza el puntaje mostrado en pantalla
    void showFishInfo(Fish *fish);  // Muestra información sobre un pez

protected:
    void paintEvent(QPaintEvent *event) override;  // Maneja el evento de pintura para dibujar la ventana del juego
    void keyPressEvent(QKeyEvent *event) override;  // Maneja la presión de teclas para el movimiento del jugador
    void keyReleaseEvent(QKeyEvent *event) override;  // Maneja la liberación de teclas para detener el movimiento del jugador
    void showEvent(QShowEvent *event) override;  // Maneja el evento de visualización de la ventana
    void resizeEvent(QResizeEvent *event) override;  // Maneja el evento de redimensionamiento de la ventana

private slots:
    void updateGameObjects();  // Actualiza la posición y estado de todos los objetos del juego

private:
    Ui::GameWindow *ui;  // Interfaz de usuario
    Player *player;  // Instancia del jugador
    bool playerPositioned;  // Flag para verificar si el jugador ha sido posicionado
    QList<GameObject *> gameObjects;  // Lista de objetos de juego como peces y basura
    int trashCollected;  // Contador de basura recogida
    int trashMissed;  // Contador de basura no recogida
    QLabel *labelTrashCollected;  // Etiqueta para mostrar la basura recogida
    QLabel *labelTrashMissed;  // Etiqueta para mostrar la basura perdida
    QPushButton *closeButton;  // Botón para cerrar el juego
    InfoFish *infoFishDialog;  // Diálogo para mostrar información de peces
    QTimer *fishTimer;  // Temporizador para generar peces
    QTimer *trashTimer;  // Temporizador para generar basura
    QTimer *timer;  // Temporizador general para actualizar el juego
    Fish *selectedFish = nullptr; // Almacena el pez seleccionado actualmente para mostrar su información
};

#endif // GAMEWINDOW_H
