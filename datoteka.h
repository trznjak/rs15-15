#ifndef DATOTEKA_H
#define DATOTEKA_H

#include <QWidget>

namespace Ui {
class Datoteka;
}

class Datoteka : public QWidget
{
    Q_OBJECT



public:
    explicit Datoteka(QWidget *parent = 0);
    ~Datoteka();

public slots:
    void ucitaj();

private:
    Ui::Datoteka *ui;
};

#endif // DATOTEKA_H
