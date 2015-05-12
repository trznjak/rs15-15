#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    graph = new Graph(this);
    linijskeKomande = new LinijskeKomande(this);
    pocetna = new Pocetna(this);
}

MainWindow::~MainWindow() {
    delete ui;
    delete graph;
    delete pocetna;
    delete linijskeKomande;
}
