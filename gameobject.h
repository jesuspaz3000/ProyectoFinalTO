#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QRect>
#include <QPainter>
#include <QColor>

class GameObject: public QObject //Herencia pública de la clase QObject
{
    Q_OBJECT //macro que brinda a la clase carácterísticas específicas de Qt
public:
    enum Shape { Square, Circle };  // Define formas posibles para el objeto
    GameObject(int x, int y, int size, Shape shape, QColor color, QObject *parent = nullptr);  // Constructor

    virtual void paint(QPainter *painter);  // Método para pintar el objeto, a sobrescribir
    virtual void updatePosition();          // Método para actualizar posición, a sobrescribir
    QRect getRect() const { return rect; }  // Obtiene el rectángulo del objeto

};

#endif // GAMEOBJECT_H
