#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QPainter>
#include <QKeyEvent>
#include "fish.h"
#include "trash.h"
#include "ecosystem.h"
#include "question.h"
#include <QMessageBox>

// Constructor de GameWindow: Configura la ventana del juego
GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::GameWindow),
    playerPositioned(false), trashCollected(0), trashMissed(0) {
    ui->setupUi(this);
    this->showMaximized(); // Maximiza la ventana al inicio

    // Inicializa el jugador y los temporizadores
    player = new Player(this, -100, -100); // Crea el jugador fuera de la pantalla

    // Configuración de los temporizadores
    fishTimer = new QTimer(this); // Temporizador para generar peces
    connect(fishTimer, &QTimer::timeout, this, &GameWindow::spawnFish);
    fishTimer->start(1000); // Inicia el temporizador con un intervalo de 1 segundo

    trashTimer = new QTimer(this); // Temporizador para generar basura
    connect(trashTimer, &QTimer::timeout, this, &GameWindow::spawnTrash);
    trashTimer->start(1000); // Inicia el temporizador con un intervalo de 1 segundo

    timer = new QTimer(this); // Temporizador general para actualizar objetos de juego
    connect(timer, &QTimer::timeout, this, &GameWindow::updateGameObjects);
    timer->start(16); // Inicia el temporizador para actualizaciones rápidas (aproximadamente 60 FPS)

    // Configuración de conexiones para actualizar y manejar colisiones
    connect(player, &Player::positionChanged, this, QOverload<>::of(&GameWindow::update));
    connect(player, &Player::collidedWithObject, this, &GameWindow::handleObjectCollision);

    // Configuración de etiquetas para mostrar puntajes
    labelTrashCollected = new QLabel(this); // Muestra la cantidad de basura recogida
    labelTrashMissed = new QLabel(this); // Muestra la cantidad de basura perdida
    labelTrashCollected->move(10, 15); // Posiciona las etiquetas
    labelTrashMissed->move(10, 35);
    updateScore(); // Actualiza el texto de las etiquetas

    // Configuración del estilo y visibilidad de las etiquetas
    labelTrashCollected->setMinimumWidth(200);
    labelTrashMissed->setMinimumWidth(200);
    labelTrashCollected->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    labelTrashMissed->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    labelTrashCollected->setStyleSheet("QLabel { color: green; font-size: 25px; margin-bottom: 10px }");
    labelTrashMissed->setStyleSheet("QLabel {  color: red; font-size: 25px; margin-top: 10px }");
    labelTrashCollected->show();
    labelTrashMissed->show();

    // Configuración del botón de cierre
    closeButton = new QPushButton("cerrar", this);
    connect(closeButton, &QPushButton::clicked, this, &GameWindow::close);
    closeButton->hide(); // Se muestra después de maximizar la ventana

    // Inicializa el diálogo para mostrar información de peces
    infoFishDialog = new InfoFish(this);
}

void GameWindow::pauseGame() {
    fishTimer->stop();
    trashTimer->stop();
    timer->stop(); // Detiene todos los temporizadores para pausar el juego
}

void GameWindow::resumeGame() {
    fishTimer->start();
    trashTimer->start();
    timer->start(); // Reanuda todos los temporizadores para continuar el juego
}

// Genera un nuevo pez en el juego y lo añade a la lista de objetos de juego
void GameWindow::spawnFish() {
    Fish *newFish = new Fish(this);
    connect(newFish, &Fish::requestInfo, this, [this, newFish]() {
        this->showFishInfo(newFish);
    });
    gameObjects.append(newFish);
}

// Maneja el evento cuando un pez sale de la pantalla, eliminándolo de la lista y liberando memoria
void GameWindow::handleFishOutOfScreen(Fish *fish) {
    gameObjects.removeOne(fish);
    fish->deleteLater();
}

void GameWindow::showFishInfo(Fish *fish) {
    selectedFish = fish; // Almacena el pez seleccionado para mostrar su información

    pauseGame(); // Pausa el juego antes de abrir el diálogo

    question questionDialog(this, fish->getPixmap());
    if (questionDialog.exec() == QDialog::Accepted) {
        QString userAnswer = questionDialog.getUserAnswer(); // Obtiene la respuesta del usuario
        bool isCorrect = userAnswer.compare(fish->getName(), Qt::CaseInsensitive) == 0;

        // Muestra un mensaje informativo sobre la corrección de la respuesta
        QMessageBox::information(this, "Respuesta",
                                 isCorrect ? "¡Correcto!" : "Incorrecto. Inténtalo de nuevo.");

        if (isCorrect) {
            trashMissed = std::max(0, trashMissed - 1); // Reduce basura perdida si la respuesta es correcta
            updateScore(); // Actualiza las etiquetas de puntaje
        }

        // Muestra información adicional sobre el pez
        InfoFish infoFishDialog(this, fish->getPixmap(), fish->getName());
        infoFishDialog.exec();
    }

    resumeGame(); // Reanuda el juego después de cerrar los diálogos
}

// Genera un nuevo objeto de basura en el juego
void GameWindow::spawnTrash() {
    Trash *newTrash = new Trash(this);
    connect(newTrash, &Trash::trashOutOfScreen, this, &GameWindow::handleTrashOutOfScreen);
    gameObjects.append(newTrash);
}

// Maneja el evento cuando un objeto de basura sale de la pantalla
void GameWindow::handleTrashOutOfScreen(Trash *trash) {
    trashMissed++;
    updateScore();
    gameObjects.removeOne(trash);
    trash->deleteLater();
}

// Actualiza el puntaje mostrado en la interfaz
void GameWindow::updateScore() {
    labelTrashCollected->setText("Eliminadas: " + QString::number(trashCollected));
    labelTrashMissed->setText("Pasadas: " + QString::number(trashMissed));
}

// Evento de pintura para dibujar la ventana del juego
void GameWindow::paintEvent(QPaintEvent *event) {
    QMainWindow::paintEvent(event);
    QPainter painter(this);
    QRect windowRect = this->rect(); // Obtiene rectángulo de la ventana
    Ecosystem ecosystem;
    ecosystem.draw(&painter, windowRect); // Dibuja el fondo del ecosistema

    // Verifica que el jugador esté posicionado antes de dibujarlo
    if (playerPositioned) {
        // Dibuja el jugador
        if (!player->getPixmap().isNull()) {
            painter.drawPixmap(player->getRect(), player->getPixmap());
        } else {
            painter.setBrush(Qt::blue);
            painter.drawRect(player->getRect());
        }
    }

    // Dibuja cada objeto del juego
    for (GameObject *obj : gameObjects) {
        obj->paint(&painter);
    }
}

// Actualiza la posición de todos los objetos del juego
void GameWindow::updateGameObjects() {
    for (GameObject *obj : gameObjects) {
        obj->updatePosition();
    }
    player->checkCollisions(gameObjects);
    update(); // Redibuja la ventana
}

// Maneja la colisión del jugador con otros objetos
void GameWindow::handleObjectCollision(GameObject* object, bool isColliding) {
    if (Fish* fish = dynamic_cast<Fish*>(object)) {
        if (isColliding) {
            fish->showInfoButton();  // Muestra el botón
        } else {
            fish->hideInfoButton();  // Oculta el botón
        }
    }

    // Corregimos la condición para Trash
    if (Trash* trash = dynamic_cast<Trash*>(object)) {
        if (isColliding) {
            // Si hay una colisión con la basura, la recoge
            trashCollected++;
            updateScore();
            gameObjects.removeOne(trash);
            trash->deleteLater();
        }
    }
}


// Maneja el evento de visualización de la ventana
void GameWindow::showEvent(QShowEvent *event) {
    QMainWindow::showEvent(event);
    QTimer::singleShot(100, this, [this]() {
        // Centraliza el jugador una vez que la ventana está maximizada
        if (!playerPositioned) {
            int centerX = this->width() / 2;
            int centerY = this->height() / 2;
            int pixmapWidth = player->getPixmap().width();
            int pixmapHeight = player->getPixmap().height();
            player->setRect(QRect(centerX - pixmapWidth / 2, centerY - pixmapHeight / 2, pixmapWidth, pixmapHeight));
            playerPositioned = true;
            update();
        }

        // Ahora que la ventana está maximizada, establece la geometría del botón y lo muestra
        closeButton->setGeometry(this->width() - 100, this->height() - 50, 80, 30);
        closeButton->show();
    });
}

// Maneja el evento de redimensionamiento de la ventana
void GameWindow::resizeEvent(QResizeEvent *event) {
    // Guarda dimensiones antiguas y calcula nuevas proporciones
    int oldWidth = event->oldSize().width();
    int oldHeight = event->oldSize().height();
    int newWidth = this->width();
    int newHeight = this->height();

    // Si no hay dimensiones antiguas válidas, retorna
    if (oldWidth == -1 || oldHeight == -1) {
        QMainWindow::resizeEvent(event);
        return;
    }

    // Calcula la nueva posición del jugador basándose en las proporciones
    float widthRatio = static_cast<float>(newWidth) / static_cast<float>(oldWidth);
    float heightRatio = static_cast<float>(newHeight) / static_cast<float>(oldHeight);
    QRect currentRect = player->getRect();
    int newX = static_cast<int>(currentRect.x() * widthRatio);
    int newY = static_cast<int>(currentRect.y() * heightRatio);
    player->setRect(QRect(newX, newY, currentRect.width(), currentRect.height()));
    // Reposiciona el botón de cierre
    closeButton->move(this->width() - 100, this->height() - 50);

    QMainWindow::resizeEvent(event);
    update(); // Redibuja la ventana
}


void GameWindow::keyPressEvent(QKeyEvent *event) {
    if (!event->isAutoRepeat()) {
        switch(event->key()) {
        // Maneja eventos de presión de teclas para el movimiento del jugador
        case Qt::Key_Left:
        case Qt::Key_A: player->moveLeft(); break;
        case Qt::Key_Right:
        case Qt::Key_D: player->moveRight(); break;
        case Qt::Key_Up:
        case Qt::Key_W: player->moveUp(); break;
        case Qt::Key_Down:
        case Qt::Key_S: player->moveDown(); break;
        }
    }
}

void GameWindow::keyReleaseEvent(QKeyEvent *event) {
    if (!event->isAutoRepeat()) {
        switch(event->key()) {
        // Maneja eventos de liberación de teclas para detener el movimiento del jugador
        case Qt::Key_Left:
        case Qt::Key_A: player->stopLeft(); break;
        case Qt::Key_Right:
        case Qt::Key_D: player->stopRight(); break;
        case Qt::Key_Up:
        case Qt::Key_W: player->stopUp(); break;
        case Qt::Key_Down:
        case Qt::Key_S: player->stopDown(); break;
        }
    }
}

// Destructor: limpia los recursos utilizados
GameWindow::~GameWindow() {
    delete ui;
    delete player;
    qDeleteAll(gameObjects);
    gameObjects.clear();
}
