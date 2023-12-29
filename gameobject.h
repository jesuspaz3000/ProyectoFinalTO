#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QRect>
#include <QPainter>
#include <QPixmap>  // Asegúrate de incluir esto para QPixmap

class GameObject : public QObject {
    Q_OBJECT

public:
    // Actualiza el constructor para usar imágenes
    GameObject(int x, int y, int size, const QString &imagePath, QObject *parent = nullptr);

    virtual void paint(QPainter *painter);  // Método para pintar el objeto, a sobrescribir
    virtual void updatePosition();          // Método para actualizar posición, a sobrescribir
    QRect getRect() const { return rect; }  // Obtiene el rectángulo del objeto

protected:
    QWidget *parentWidget;  // Widget padre del objeto
    QRect rect;             // Rectángulo que define posición y tamaño
    QPixmap pixmap;         // Imagen del objeto
    bool movingLeft;        // Indica si se mueve hacia la izquierda
    int speed;              // Velocidad de movimiento
};

#endif // GAMEOBJECT_H
