#include "fish.h"
#include <QRandomGenerator>
#include <QWidget>
#include <QTransform>
#include "gamewindow.h"

// Lista de imágenes de peces y sus nombres
const QList<QString> fishImages = { ":/img/images/ballena.png", ":/img/images/delfin.png",
                                   ":/img/images/pezEspada.png", ":/img/images/pirana.png",
                                   ":/img/images/tiburon.png" };
const QList<QString> fishNames = { "ballena", "delfin", "pez espada", "pirana", "tiburon" };

// Constructor: inicializa un objeto Fish con una imagen de pez aleatoria
Fish::Fish(QObject *parent, float scaleFactor)
    : GameObject(0, 0, 50 * scaleFactor, "", parent), scaleFactor(scaleFactor) {
    QWidget *widget = static_cast<QWidget*>(parent);
    int height = widget->height();
    int width = widget->width();

    // Elige una imagen de pez de forma aleatoria
    int fishIndex = QRandomGenerator::global()->bounded(fishImages.size());
    QString fishImage = fishImages[fishIndex];
    fishName = fishNames[fishIndex];  // Guarda el nombre del pez

    // Carga la imagen del pez y aplica la transformación de escala
    pixmap.load(fishImage);
    QTransform transform;
    transform.scale(scaleFactor, scaleFactor);
    pixmap = pixmap.transformed(transform);

    // Ajusta el tamaño y posición inicial del rectángulo
    rect.setSize(pixmap.size());
    int yMargin = height * 0.2;
    int yPos = QRandomGenerator::global()->bounded(yMargin, height - yMargin);
    int xPos = QRandomGenerator::global()->bounded(2) ? -rect.width() : width;
    rect.moveTo(xPos, yPos);

    movingLeft = xPos > 0;
    if (!movingLeft) {
        // Refleja la imagen si se mueve hacia la izquierda
        pixmap = pixmap.transformed(QTransform().scale(-1, 1));
    }

    speed = 1;

    // En el constructor de Fish o donde inicializas infoButton
    infoButton = new QPushButton("Info", static_cast<QWidget*>(parent));
    infoButton->move(rect.x(), rect.y());
    infoButton->hide();
    connect(infoButton, &QPushButton::clicked, this, &Fish::infoButtonClicked, Qt::UniqueConnection);
}


// Actualiza la posición del pez en cada frame
void Fish::updatePosition() {
    int dx = (movingLeft ? -speed : speed);  // Calcula desplazamiento horizontal
    rect.translate(dx, 0);  // Mueve el pez horizontalmente

    // Emite señal si el pez sale de la pantalla
    if (rect.right() < 0 || rect.left() > parentWidget->width()) {
        emit fishOutOfScreen(this);  // Notifica que el pez salió de la pantalla
    }

    // Actualiza la posición del botón "Info" solo si está visible
    if (infoButton->isVisible()) {
        centerInfoButton();
    }
}

void Fish::showInfoButton() {
    centerInfoButton();
    infoButton->show();
}

QPixmap Fish::getPixmap() const {
    return pixmap;
}

QString Fish::getName() const {
    return fishName;
}

void Fish::centerInfoButton() {
    // Calcula el centro del pez
    int centerX = rect.x() + rect.width() / 2;
    int centerY = rect.y() + rect.height() / 2;

    // Ajusta la posición del botón "Info" para que esté centrado
    infoButton->move(centerX - infoButton->width() / 2, centerY - infoButton->height() / 2);
}

void Fish::hideInfoButton() {
    infoButton->hide();
}

void Fish::infoButtonClicked() {
    GameWindow *gameWindow = qobject_cast<GameWindow*>(parentWidget);
    if (gameWindow) {
        gameWindow->pauseGame();
    }
    // No llamar a questionDialog.exec() aquí
    if (gameWindow) {
        gameWindow->resumeGame();
    }
    emit requestInfo(); // Emitir la señal una sola vez
}
