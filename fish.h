#ifndef FISH_H
#define FISH_H

#include <QObject>
#include <QPushButton>
#include "gameobject.h"

class Fish : public GameObject {
    Q_OBJECT

public:
    explicit Fish(QObject *parent = nullptr, float scaleFactor = 1.2f);  // Constructor modificado

    void updatePosition() override;
    void showInfoButton();
    void hideInfoButton();
    void centerInfoButton();
    QPixmap getPixmap() const;
    QString getName() const;

signals:
    void fishOutOfScreen(Fish *fish);
    void requestInfo();

private:
    float scaleFactor;  // Factor de escala para el tamaño del pez
    QPushButton *infoButton;
    QString fishName;  // Nombre del pez

private slots:
    void infoButtonClicked();
};

#endif // FISH_H
