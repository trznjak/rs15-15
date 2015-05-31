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
    void set_flag_dialog();
    explicit Pocetna(QWidget *parent = 0);
    ~Pocetna();


public slots:
   void prikaziLinijskeKomande();
   void prikaziGraph();
   void prikaziDatoteku();

private:
    bool flag_dialog;
    Ui::Pocetna *ui;
    QWidget* widgetLinijskeKomande;
    QWidget* widgetGraph;
    QWidget* widgetDatoteka;
};

#endif // POCETNA_H
