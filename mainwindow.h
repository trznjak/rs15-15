#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "graph.h"
#include "linijskekomande.h"
#include "pocetna.h"
#include "linijskekomande.h"

#include <QMainWindow>
#include <QDebug>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpacerItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void back();

private:
    Ui::MainWindow *ui;

    Graph *graph;
    Pocetna *pocetna;
    LinijskeKomande *linijskeKomande;

};

#endif // MAINWINDOW_H
