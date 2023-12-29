#include "gameobject.h"
#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QRandomGenerator>

// Constructor: Inicializa un GameObject con una imagen
GameObject::GameObject(int x, int y, int size, const QString &imagePath, QObject *parent)
    : QObject(parent), rect(x, y, size, size), pixmap(imagePath), movingLeft(QRandomGenerator::global()->bounded(2)), speed(2) {
    parentWidget = qobject_cast<QWidget*>(parent);
    pixmap = pixmap.scaled(size, size, Qt::KeepAspectRatio);  // Escala la imagen
}

// Método para pintar el GameObject
void GameObject::paint(QPainter *painter) {
    painter->drawPixmap(rect, pixmap);  // Dibuja la imagen
}

// Actualiza la posición del GameObject
void GameObject::updatePosition() {
    if (!parentWidget) return;  // Verifica si hay un widget padre

    int dx = (movingLeft ? -speed : speed);  // Calcula desplazamiento horizontal
    rect.translate(dx, 0);  // Mueve el objeto horizontalmente
}
