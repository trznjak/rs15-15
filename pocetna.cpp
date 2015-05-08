#include "pocetna.h"
#include "ui_pocetna.h"
#include "dialog.h"
#include "linijskekomande.h"

Pocetna::Pocetna(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pocetna)
{
    ui->setupUi(this);

    QPixmap pixmap("graf.png");
    QIcon buttonIcon(pixmap);
    ui->pushButton->setIcon(buttonIcon);
    ui->pushButton->setIconSize(QSize(150, 150));

    QPixmap pixmap_2("instrukcije.png");
    QIcon buttonIcon_2(pixmap_2);
    ui->pushButton_2->setIcon(buttonIcon_2);
    ui->pushButton_2->setIconSize(QSize(150, 150));

    QPixmap pixmap_3("folder.jpg");
    QIcon buttonIcon_3(pixmap_3);
    ui->pushButton_3->setIcon(buttonIcon_3);
    ui->pushButton_3->setIconSize(QSize(150, 150));

    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(prikaziLinijskeKomande()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(prikaziGraph()));
    widgetLinijskeKomande = parent->findChild<QWidget*>("LinijskeKomande");
    widgetGraph = parent->findChild<QWidget*>("Graph");

}

void Pocetna::prikaziLinijskeKomande()
{
    widgetLinijskeKomande->setVisible(true);
    this->setVisible(false);
}

Pocetna::~Pocetna()
{
    delete ui;
}

void Pocetna::prikaziGraph() {
    widgetGraph->setVisible(true);
    this->setVisible(false);
}



