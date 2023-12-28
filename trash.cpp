#include "trash.h"
#include <QRandomGenerator>
#include <QWidget>

// Constructor de Trash: inicializa un objeto Trash con posición y características aleatorias
Trash::Trash(QObject *parent, float scaleFactor)
    : GameObject(QRandomGenerator::global()->bounded(static_cast<QWidget*>(parent)->width()),
                 -50,// Inicia justo fuera de la vista en la parte superior
                 50 * scaleFactor, ":/img/images/basura.png", parent), scaleFactor(scaleFactor) {
    QTransform transform;
    transform.scale(scaleFactor, scaleFactor);
    pixmap = pixmap.transformed(transform);

    rect.setSize(pixmap.size());
    speed = 1;// Establece velocidad de caída

}

// Actualiza la posición de Trash en cada frame
void Trash::updatePosition() {
    int dy = speed;// Calcula el desplazamiento vertical
    rect.translate(0, dy);// Mueve el objeto hacia abajo

    // Verifica si la basura ha salido de la pantalla
    if (rect.top() > parentWidget->height()) {
        emit trashOutOfScreen(this);// Emite señal si sale de la pantalla
    }
}

