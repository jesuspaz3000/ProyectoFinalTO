#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QRect>
#include <QTimer>
#include <QPixmap>
#include <QWidget>
#include "gameobject.h"

class Player : public QObject {
    Q_OBJECT
public:
    Player(QWidget *parentWidget, int x, int y);  // Constructor del jugador

    void moveLeft();  // Mueve el jugador hacia la izquierda
    void moveRight();  // Mueve el jugador hacia la derecha
    void moveUp();  // Mueve el jugador hacia arriba
    void moveDown();  // Mueve el jugador hacia abajo
    void stopLeft();  // Detiene movimiento hacia la izquierda
    void stopRight();  // Detiene movimiento hacia la derecha
    void stopUp();  // Detiene movimiento hacia arriba
    void stopDown();  // Detiene movimiento hacia abajo

    void setRect(const QRect &newRect);  // Establece el rectángulo del jugador

    QRect getRect() const;  // Obtiene el rectángulo del jugador
    QPixmap getPixmap() const;  // Obtiene el pixmap (imagen) del jugador
    void checkCollisions(const QList<GameObject*>& gameObjects);  // Verifica colisiones

signals:
    void positionChanged();  // Señal emitida cuando cambia la posición
    void collidedWithObject(GameObject* obj);  // Señal emitida en colisión

private:
    QWidget *parentWidget;  // Widget padre del jugador
    QRect rect;             // Rectángulo que representa la posición y tamaño
    QPixmap pixmap;         // Imagen del jugador
    int speed;              // Velocidad del jugador
    QTimer *timer;          // Temporizador para actualizaciones
    bool movingLeft, movingRight, movingUp, movingDown;  // Direcciones de movimiento
    int dx, dy;             // Desplazamiento en x y y

private slots:
    void updatePosition();  // Actualiza la posición del jugador
};
#endif // PLAYER_H
