// infofish.h
#ifndef INFOFISH_H
#define INFOFISH_H

#include <QDialog>
#include <QPixmap>

namespace Ui {
class InfoFish;
}

class InfoFish : public QDialog
{
    Q_OBJECT

public:
    explicit InfoFish(QWidget *parent = nullptr, const QPixmap &fishPixmap = QPixmap(), const QString &fishName = QString());
    ~InfoFish();
    QString getFishDescription(const QString &fishName);
    void setFishDescription(const QString &fishName);

private slots:
    void on_aceptar_clicked();

private:
    Ui::InfoFish *ui;
};

#endif // INFOFISH_H
