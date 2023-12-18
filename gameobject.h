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
    GameObject();
};

#endif // GAMEOBJECT_H
