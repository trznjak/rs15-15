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
//    QPushButton *back = new QPushButton("Back", this);

//    QVBoxLayout *vbox = new QVBoxLayout(this);
//    vbox->addWidget(back);
//    vbox->addWidget(graph);
//    vbox->addWidget(pocetna);
//    vbox->addWidget(linijskeKomande);
//    vbox->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//    ui->centralWidget->setLayout(vbox);
    ui->centralWidget->layout()->addWidget(pocetna);
    ui->centralWidget->layout()->addWidget(graph);
    ui->centralWidget->layout()->addWidget(linijskeKomande);
    ui->centralWidget->layout()->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);


    QObject::connect(ui->back, SIGNAL(clicked()), this, SLOT(back()));
}

MainWindow::~MainWindow() {
    delete ui;
    delete graph;
    delete pocetna;
    delete linijskeKomande;
}

void MainWindow::back() {
    QWidget *widgetLinijskeKomande = this->findChild<QWidget* >("LinijskeKomande");
    QWidget *widgetGraph = this->findChild<QWidget* >("Graph");
    QWidget *widgetPocetna = this->findChild<QWidget* >("Pocetna");

    widgetLinijskeKomande->setVisible(false);
    widgetGraph->setVisible(false);
    widgetPocetna->setVisible(true);

}
