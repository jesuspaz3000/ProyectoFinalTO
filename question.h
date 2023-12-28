#ifndef QUESTION_H
#define QUESTION_H

#include <QDialog>
#include <QPixmap>

namespace Ui {
class question;
}

class question : public QDialog
{
    Q_OBJECT

public:
    explicit question(QWidget *parent = nullptr, const QPixmap &fishPixmap = QPixmap());
    ~question();
    QString getUserAnswer() const;

private slots:
    void on_aceptar_clicked();

private:
    Ui::question *ui;
};

#endif // QUESTION_H
