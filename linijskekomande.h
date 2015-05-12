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

private:
    Ui::LinijskeKomande *ui;
    QSignalMapper *qp;
    QSignalMapper *qp1;
};

#endif // LINIJSKEKOMANDE_H
