#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pocetna.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget_3->setParent(new Graph(this));
    ui->widget_2->setParent(new LinijskeKomande(this));
    ui->widget->setParent(new Pocetna(this));
}

MainWindow::~MainWindow() {
    delete ui;
}
