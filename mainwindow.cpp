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
    pocetna = new Pocetna(this);


    instructionLab = InstructionLab::instance();
    ui->centralWidget->layout()->addWidget(pocetna);
    ui->centralWidget->layout()->addWidget(graph);
    ui->centralWidget->layout()->addWidget(linijskeKomande);
    ui->centralWidget->layout()->addWidget(datoteka);
    ui->centralWidget->layout()->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    ui->back->hide();
    ui->next->hide();
    QObject::connect(ui->back, SIGNAL(clicked()), this, SLOT(back()));
    QObject::connect(this, SIGNAL(next()), instructionLab, SLOT(fromGraphToString()));
}

MainWindow::~MainWindow() {
    delete ui;
    delete graph;
    delete pocetna;
    delete linijskeKomande;
}

void MainWindow::showBackNext() {
    ui->back->show();
    ui->next->show();
}

void MainWindow::back() {
    QWidget *widgetLinijskeKomande = this->findChild<QWidget* >("LinijskeKomande");
    QWidget *widgetGraph = this->findChild<QWidget* >("Graph");
    QWidget *widgetPocetna = this->findChild<QWidget* >("Pocetna");
    QWidget *widgetDatoteka = this->findChild<QWidget* >("Datoteka");

    widgetLinijskeKomande->setVisible(false);
    widgetGraph->setVisible(false);
    widgetDatoteka->setVisible(false);
    widgetPocetna->setVisible(true);

}


void MainWindow::on_next_clicked() {
    emit next();
}
