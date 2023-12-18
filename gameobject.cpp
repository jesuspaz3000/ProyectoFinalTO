#include "gameobject.h"
#include <QWidget>
#include <QRandomGenerator>

// Constructor: Inicializa un GameObject
GameObject::GameObject(int x, int y, int size, Shape shape, QColor color, QObject *parent)
    : QObject(parent), rect(x, y, size, size), shape(shape), color(color),
    movingLeft(QRandomGenerator::global()->bounded(2)), speed(2) {
    parentWidget = qobject_cast<QWidget*>(parent);  // Convierte el objeto padre a QWidget
}
