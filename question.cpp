#include "question.h"
#include "ui_question.h"

question::question(QWidget *parent, const QPixmap &fishPixmap)
    : QDialog(parent),
    ui(new Ui::question) {
    ui->setupUi(this);

    if (!fishPixmap.isNull()) {
        QLabel *imagenPez = ui->imagenPez; 
        if (imagenPez) {
            // Escala la imagen a un % del tamaño del QLabel
            QSize newSize = imagenPez->size() * 3;
            imagenPez->setPixmap(fishPixmap.scaled(newSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }
}

question::~question() {
    delete ui;
}

void question::on_aceptar_clicked() {
    qDebug() << "Aceptar clicked, user answer:" << ui->nombrePez->text();
    accept();
}

QString question::getUserAnswer() const {
    return ui->nombrePez->text();
}
