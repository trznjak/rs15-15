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
//    qDebug() << ui->stackedWidget->currentIndex();
//    ui->stackedWidget->insertWidget(0, new Pocetna(this));
//    ui->stackedWidget->insertWidget(1, new Graph(this));
}

MainWindow::~MainWindow() {
    delete ui;
    delete graph;
    delete pocetna;
    delete linijskeKomande;
}
