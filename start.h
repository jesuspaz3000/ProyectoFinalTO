#ifndef START_H
#define START_H

#include <QWidget>
#include <QKeyEvent>
#include <QPixmap>

namespace Ui {
class Start;  // Clase de interfaz de usuario para la ventana de inicio
}

class Start : public QWidget {
    Q_OBJECT

public:
    explicit Start(QWidget *parent = nullptr);  // Constructor de la ventana de inicio
    ~Start();  // Destructor

    void keyPressEvent(QKeyEvent *event) override;  // Reimplementación del evento de presión de tecla
    void paintEvent(QPaintEvent *event) override;

private slots:
    void on_pushButton_clicked();  // Manejador del clic en el botón de inicio

private:
    void startGame();  // Función para iniciar el juego
    Ui::Start *ui;  // Interfaz de usuario
    QPixmap background;
    void drawBackground(QPainter *painter, const QRect& rect); // Función para dibujar el ecosistema
};

#endif // START_H
