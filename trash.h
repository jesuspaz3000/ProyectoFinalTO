#ifndef TRASH_H
#define TRASH_H

#include "gameobject.h"

class Trash : public GameObject {
    Q_OBJECT

public:
    explicit Trash(QObject *parent = nullptr, float scaleFactor = 1.3f);  // Constructor modificado
    void updatePosition() override;

signals:
    void trashOutOfScreen(Trash *trash);

private:
    float scaleFactor;  // Factor de escala para el tamaño del objeto de basura
};

#endif // TRASH_H
