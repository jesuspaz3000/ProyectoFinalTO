#include "fish.h"
#include <QRandomGenerator>
#include <QWidget>

// Constructor: inicializa un objeto Fish
Fish::Fish(QObject *parent)
    : GameObject(0, 0, 50, GameObject::Circle, Qt::blue, parent) {
    QWidget *widget = static_cast<QWidget*>(parent);  // Convierte el objeto padre a QWidget
    int height = widget->height();  // Altura del widget padre
    int width = widget->width();    // Anchura del widget padre

    // Calcula posición y aleatoria dentro de un margen vertical
    int yMargin = height * 0.2;
    int yPos = QRandomGenerator::global()->bounded(yMargin, height - yMargin);

    // Establece posición x inicial en un lado aleatorio
    int xPos = QRandomGenerator::global()->bounded(2) ? -rect.width() : width;
    rect.moveTo(xPos, yPos);

    // Determina dirección del movimiento basada en posición inicial
    movingLeft = xPos > 0;  // Si está a la derecha, se moverá hacia la izquierda
    speed = 2;              // Establece velocidad de movimiento
}

// Actualiza la posición del pez en cada frame
void Fish::updatePosition() {
    int dx = (movingLeft ? -speed : speed);  // Calcula desplazamiento horizontal
    rect.translate(dx, 0);  // Mueve el pez horizontalmente

    // Emite señal si el pez sale de la pantalla
    if (rect.right() < 0 || rect.left() > parentWidget->width()) {
        emit fishOutOfScreen(this);  // Notifica que el pez salió de la pantalla
    }
}
