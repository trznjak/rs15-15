#ifndef LINIJSKEKOMANDE_H
#define LINIJSKEKOMANDE_H

#include <QWidget>
#include <QSignalMapper>

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
    void ispisi();
    void ocisti();
    void obrisi();

private:
    Ui::LinijskeKomande *ui;
    QSignalMapper *qp;
    QSignalMapper *qp1;
    QSignalMapper *qp2;
};

#endif // LINIJSKEKOMANDE_H
