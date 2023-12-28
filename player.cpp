#include "player.h"
#include "gameobject.h"

// Constructor del jugador: inicializa propiedades y configura el timer
Player::Player(QWidget *parentWidget, int x, int y)
    : QObject(parentWidget),
    parentWidget(parentWidget),
    rect(QRect(x, y, 0, 0)),
    pixmap(":/img/images/SubmarinoRobotico.png"),  // Carga la imagen del submarino
    speed(2),                                     // Establece velocidad inicial
    timer(new QTimer(this)),                      // Inicializa timer
    movingLeft(false), movingRight(false),        // Inicializa direcciones de movimiento
    movingUp(false), movingDown(false),
    dx(0), dy(0) {
    rect.setSize(pixmap.size());                  // Ajusta tamaño del rectángulo al de la imagen
    connect(timer, &QTimer::timeout, this, &Player::updatePosition);  // Conecta timer con actualización de posición
    timer->start(3);                              // Inicia el timer
}

// Actualiza la posición del jugador basándose en el movimiento actual
void Player::updatePosition() {
    // Calcula el desplazamiento propuesto
    int proposed_dx = (movingRight - movingLeft) * speed;
    int proposed_dy = (movingDown - movingUp) * speed;

    // Tamaño de la ventana del widget padre
    QSize windowSize = parentWidget->size();

    // Calcula la nueva posición propuesta y ajusta para mantener dentro de los límites
    QRect proposedRect = rect.translated(proposed_dx, proposed_dy);
    if (proposedRect.left() < 0) proposedRect.moveLeft(0);
    if (proposedRect.top() < 0) proposedRect.moveTop(0);
    if (proposedRect.right() > windowSize.width()) proposedRect.moveRight(windowSize.width());
    if (proposedRect.bottom() > windowSize.height()) proposedRect.moveBottom(windowSize.height());

    rect = proposedRect;
    emit positionChanged();  // Emite señal de cambio de posición
}

// Verifica colisiones con otros objetos del juego
void Player::checkCollisions(const QList<GameObject*>& gameObjects) {
    for (GameObject* obj : gameObjects) {
        bool isCurrentlyColliding = obj->getRect().intersects(this->getRect());
        emit collidedWithObject(obj, isCurrentlyColliding);
    }
}


// Métodos para iniciar y detener movimiento en diferentes direcciones
void Player::moveLeft() { movingLeft = true; }
void Player::moveRight() { movingRight = true; }
void Player::moveUp() { movingUp = true; }
void Player::moveDown() { movingDown = true; }
void Player::stopLeft() { movingLeft = false; }
void Player::stopRight() { movingRight = false; }
void Player::stopUp() { movingUp = false; }
void Player::stopDown() { movingDown = false; }

// Getter y Setter para el rectángulo del jugador
QRect Player::getRect() const {
    return rect;
}

void Player::setRect(const QRect &newRect) {
    rect = newRect;
    emit positionChanged();
}

// Getter para el QPixmap del jugador
QPixmap Player::getPixmap() const {
    return pixmap;
}