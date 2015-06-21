#ifndef DATOTEKA_H
#define DATOTEKA_H

#include <QWidget>

#include "instructionlab.h"

class InstructionLab;

namespace Ui {
class Datoteka;
}

class Datoteka : public QWidget {
    Q_OBJECT

public:
    explicit Datoteka(QWidget *parent = 0);
    ~Datoteka();

public slots:
    void ucitaj();

signals:
    void losaKomanda();
    void upaliNext();

private:
    Ui::Datoteka *ui;


    InstructionLab *instructionLab;
    QVector<QString> instructions;

    bool flag; //da li postoji losa komanda
};

#endif // DATOTEKA_H
