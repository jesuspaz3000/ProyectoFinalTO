#include "start.h"
#include "ui_start.h"
#include "gamewindow.h"
#include <QKeyEvent>
#include <QPainter>
#include <QMainWindow>


Start::Start(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Start) {
    ui->setupUi(this);  // Configura la interfaz de usuario según la definición en el archivo .ui
    background.load(":/img/images/Mar.png");
}

Start::~Start() {
    delete ui;  // Libera la memoria de la interfaz de usuario
}

void Start::on_pushButton_clicked() {
    startGame();
}

void Start::startGame() {
    // Crea y muestra una instancia de GameWindow
    GameWindow *gameWindow = new GameWindow();
    gameWindow->show();

    // Cierra la ventana actual (Start)
    this->close();
}

void Start::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        startGame();
    } else {
        QWidget::keyPressEvent(event);  // Propaga el evento al widget base si no es Enter o Return
    }
}

void Start::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QRect windowRect = this->rect(); // Obtiene rectángulo de la ventana

    // Escala el fondo para ajustarse al rectángulo manteniendo la relación de aspecto
    QPixmap scaledBg = background.scaled(windowRect.size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    // Calcula coordenadas para centrar la imagen en el rectángulo
    int x = (windowRect.width() - scaledBg.width()) / 2;
    int y = (windowRect.height() - scaledBg.height()) / 2;

    // Crea un nuevo rectángulo centrado para la imagen
    QRect centeredRect(x, y, scaledBg.width(), scaledBg.height());

    // Ajusta x si la imagen es más ancha que la ventana
    if (scaledBg.width() > windowRect.width()) {
        centeredRect.moveLeft(0);
    }

    // Ajusta y si la imagen es más alta que la ventana
    if (scaledBg.height() > windowRect.height()) {
        centeredRect.moveTop(0);
    }

    // Dibuja la imagen escalada en el rectángulo centrado
    painter.drawPixmap(centeredRect, scaledBg);
}
