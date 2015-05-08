#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget->setParent(new Graph(this));
//    ui->widget->setParent(new LinijskeKomande(this));
}

MainWindow::~MainWindow() {
    delete ui;
}
