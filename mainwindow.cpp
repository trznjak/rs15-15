#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    graph = new Graph(this);
    linijskeKomande = new LinijskeKomande(this);
    datoteka = new Datoteka(this);
    traka = new QWidget(this); //TODO: da se zameni za instancu trake
    traka->setVisible(false);
    pocetna = new Pocetna(this);


    instructionLab = InstructionLab::instance();
    ui->centralWidget->layout()->addWidget(pocetna);
    ui->centralWidget->layout()->addWidget(graph);
    ui->centralWidget->layout()->addWidget(linijskeKomande);
    ui->centralWidget->layout()->addWidget(datoteka);
    ui->centralWidget->layout()->addWidget(traka);
    ui->centralWidget->layout()->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    ui->back->hide();
    ui->next->hide();
    QObject::connect(ui->back, SIGNAL(clicked()), this, SLOT(back()));
    QObject::connect(ui->next, SIGNAL(clicked()), instructionLab, SLOT(setInVectorFromGraph()));
    QObject::connect(ui->next, SIGNAL(clicked()), this, SLOT(tapeAnimation()));
    QObject::connect(datoteka, SIGNAL(losaKomanda()), this, SLOT(ugasiNext()));
    QObject::connect(datoteka, SIGNAL(upaliNext()), this, SLOT(upaliNext()));

}

MainWindow::~MainWindow() {
    delete ui;
    delete graph;
    delete pocetna;
    delete linijskeKomande;
}

void MainWindow::showBack() {
    ui->back->show();
}

void MainWindow::back() {
    QWidget *widgetLinijskeKomande = this->findChild<QWidget* >("LinijskeKomande");
    QWidget *widgetGraph = this->findChild<QWidget* >("Graph");
    QWidget *widgetPocetna = this->findChild<QWidget* >("Pocetna");
    QWidget *widgetDatoteka = this->findChild<QWidget* >("Datoteka");

    widgetLinijskeKomande->setVisible(false);
    widgetGraph->setVisible(false);
    widgetDatoteka->setVisible(false);
    ui->back->setVisible(false);
    ui->next->setVisible(false);
    widgetPocetna->setVisible(true);

}

void MainWindow::ugasiNext() {
    ui->next->setVisible(false);
}

void MainWindow::upaliNext() {
    ui->next->setVisible(true);
}


void MainWindow::on_next_clicked() {
    emit next();
}

void MainWindow::tapeAnimation() {
    QWidget *widgetLinijskeKomande = this->findChild<QWidget* >("LinijskeKomande");
    QWidget *widgetGraph = this->findChild<QWidget* >("Graph");
    QWidget *widgetDatoteka = this->findChild<QWidget* >("Datoteka");

    widgetLinijskeKomande->setVisible(false);
    widgetGraph->setVisible(false);
    widgetDatoteka->setVisible(false);
    ui->next->setVisible(false);
    traka->setVisible(true);
    ui->back->setVisible(true);
}
