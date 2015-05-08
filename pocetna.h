#ifndef POCETNA_H
#define POCETNA_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class Pocetna;
}

class Pocetna : public QWidget
{
    Q_OBJECT

public:
    explicit Pocetna(QWidget *parent = 0);
    ~Pocetna();


public slots:
   void prikaziLinijskeKomande();
   void prikaziGraph();

private:
    Ui::Pocetna *ui;
    QWidget* widgetLinijskeKomande;
    QWidget* widgetGraph;
};

#endif // POCETNA_H
