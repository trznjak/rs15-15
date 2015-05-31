#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "graph.h"
#include "linijskekomande.h"
#include "pocetna.h"
#include "instructionlab.h"
#include "datoteka.h"

#include <QObject>
#include <QMainWindow>
#include <QDebug>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpacerItem>

class Graph;
class LinijskeKomande;
class Pocetna;
class InstructionLab;
class Datoteka;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void showBackNext();

public slots:
    void back();

signals:
    void next();

private slots:
    void on_next_clicked();

private:
    Ui::MainWindow *ui;

    Graph *graph;
    Pocetna *pocetna;
    LinijskeKomande *linijskeKomande;
    Datoteka *datoteka;

    InstructionLab *instructionLab;

};

#endif // MAINWINDOW_H
