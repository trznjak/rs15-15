#ifndef LINIJSKEKOMANDE_H
#define LINIJSKEKOMANDE_H

#include <QWidget>
#include <QSignalMapper>
#include "instructionlab.h"
class InstructionLab;
namespace Ui {
class LinijskeKomande;
}

class LinijskeKomande : public QWidget
{
    Q_OBJECT

public:

    explicit LinijskeKomande(QWidget *parent = 0);
    ~LinijskeKomande();
public slots:
    void salji_dalje();
    void ispisi();
    void ocisti();
    void obrisi();

private:
    QVector<QString> ispravne_linije; //ovde smestam ispravne linije
    Ui::LinijskeKomande *ui;
    QSignalMapper *qp;
    QSignalMapper *qp1;
    QSignalMapper *qp2;
    InstructionLab *inst;
};

#endif // LINIJSKEKOMANDE_H
