#include "gameobject.h"
#include <QWidget>
#include <QRandomGenerator>

// Constructor: Inicializa un GameObject
GameObject::GameObject(int x, int y, int size, Shape shape, QColor color, QObject *parent)
    : QObject(parent), rect(x, y, size, size), shape(shape), color(color),
    movingLeft(QRandomGenerator::global()->bounded(2)), speed(2) {
    parentWidget = qobject_cast<QWidget*>(parent);  // Convierte el objeto padre a QWidget
}

// Método para pintar el GameObject
void GameObject::paint(QPainter *painter) {
    painter->setBrush(color);  // Configura el color del pincel
    switch (shape) {
    case Square:
        painter->drawRect(rect);  // Dibuja un cuadrado
        break;
    case Circle:
        painter->drawEllipse(rect);  // Dibuja un círculo
        break;
    }
}

// Actualiza la posición del GameObject
void GameObject::updatePosition() {
    if (!parentWidget) return;  // Verifica si hay un widget padre

    int dx = (movingLeft ? -speed : speed);  // Calcula desplazamiento horizontal
    rect.translate(dx, 0);  // Mueve el objeto horizontalmente
}
