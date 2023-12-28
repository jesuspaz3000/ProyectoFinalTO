#ifndef FISH_H
#define FISH_H

#include <QObject>
#include "gameobject.h"

class Fish : public GameObject {
    Q_OBJECT

public:
    explicit Fish(QObject *parent = nullptr);  // Constructor de Fish

    void updatePosition() override;  // Actualiza posición del pez

signals:
    void fishOutOfScreen(Fish *fish);  // Señal cuando el pez sale de pantalla
};

#endif // FISH_H
