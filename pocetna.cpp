#include "pocetna.h"
#include "ui_pocetna.h"
#include "dialog.h"
#include "linijskekomande.h"
#include "graph.h"
#include "datoteka.h"

Pocetna::Pocetna(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pocetna)
{
    ui->setupUi(this);

    QPixmap pixmap("://graph.png");
    QIcon buttonIcon(pixmap);
    ui->pushButton->setIcon(buttonIcon);
    ui->pushButton->setIconSize(QSize(200, 200));

    QPixmap pixmap_2("://code.png");
    QIcon buttonIcon_2(pixmap_2);
    ui->pushButton_2->setIcon(buttonIcon_2);
    ui->pushButton_2->setIconSize(QSize(200, 200));

    QPixmap pixmap_3("://file.png");
    QIcon buttonIcon_3(pixmap_3);
    ui->pushButton_3->setIcon(buttonIcon_3);
    ui->pushButton_3->setIconSize(QSize(200, 200));

    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(prikaziLinijskeKomande()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(prikaziGraph()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(prikaziDatoteku()));
    widgetLinijskeKomande = parent->findChild<QWidget* >("LinijskeKomande");
    widgetGraph = parent->findChild<QWidget* >("Graph");
    widgetDatoteka = parent->findChild<QWidget* >("Datoteka");

    flag_dialog=false;
}

Pocetna::~Pocetna() {
    delete ui;
}

void Pocetna::prikaziLinijskeKomande()
{
    tipUnosa = INPUT_TYPE::LINECOMMAND;
    widgetLinijskeKomande->setVisible(true);
    this->setVisible(false);
    dynamic_cast<MainWindow* >(this->parent()->parent())->showBack();
    if(!flag_dialog)
    {
        Dialog qd(this);
        qd.exec();
    }
}


void Pocetna::prikaziGraph() {
    tipUnosa = INPUT_TYPE::GRAPH;
    widgetGraph->setVisible(true);
    this->setVisible(false);

    MainWindow *mw = dynamic_cast<MainWindow* >(this->parent()->parent());
    mw->showBack();
    mw->upaliNext();
}

void Pocetna::prikaziDatoteku(){
    tipUnosa = INPUT_TYPE::FILE_I;
    widgetDatoteka->setVisible(true);
    this->setVisible(false);
    dynamic_cast<MainWindow* >(this->parent()->parent())->showBack();
}

void Pocetna::set_flag_dialog()
{
    flag_dialog=true;
}


