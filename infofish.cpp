// infofish.cpp
#include "infofish.h"
#include "ui_infofish.h"

InfoFish::InfoFish(QWidget *parent, const QPixmap &fishPixmap, const QString &fishName)
    : QDialog(parent), ui(new Ui::InfoFish)
{
    ui->setupUi(this);

    if (!fishPixmap.isNull()) {
        QLabel *imagenInfoFish = ui->imagenInfoFish; // Asegúrate de usar el nombre correcto del QLabel
        if (imagenInfoFish) {
            // Escala la imagen a un tamaño mayor
            QSize newSize = imagenInfoFish->size() * 3; // Ajusta el factor de escala según sea necesario
            imagenInfoFish->setPixmap(fishPixmap.scaled(newSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }

    ui->nombrePez->setText(fishName);
    ui->infoPez->setText(fishName + ": " + getFishDescription(fishName));
    setFishDescription(fishName);
}

InfoFish::~InfoFish() {
    delete ui;
}

void InfoFish::on_aceptar_clicked() {
    accept();
}

QString InfoFish::getFishDescription(const QString &fishName) {
    if (fishName == "ballena") {
        return "Mamífero marino gigante, conocido por su canto único.";
    } else if (fishName == "delfin") {
        return "Inteligente y juguetón, famoso por su comunicación acústica.";
    } else if (fishName == "pez espada") {
        return "Pez agresivo con un pico largo y puntiagudo similar a una espada.";
    } else if (fishName == "piraña") {
        return "Pez de agua dulce conocido por sus dientes afilados y comportamiento depredador.";
    } else if (fishName == "tiburon") {
        return "Impresionante depredador marino, famoso por sus dientes afilados y gran velocidad.";
    }
    return "Información no disponible.";
}

void InfoFish::setFishDescription(const QString &fishName) {
    QString description = getFishDescription(fishName);

    // Ajuste de tamaño de fuente (opcional)
    QFont font = ui->infoPez->font();
    font.setPointSize(10); // Puedes ajustar el tamaño según sea necesario
    ui->infoPez->setFont(font);

    // Habilita el ajuste de palabras
    ui->infoPez->setWordWrap(true);

    // Establece el texto
    ui->infoPez->setText(description);
}
