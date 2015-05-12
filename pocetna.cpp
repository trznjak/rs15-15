#include "pocetna.h"
#include "ui_pocetna.h"
#include "dialog.h"
#include "linijskekomande.h"
#include "graph.h"

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
    widgetLinijskeKomande = parent->findChild<QWidget* >("LinijskeKomande");
    widgetGraph = parent->findChild<Graph* >("Graph");

}

void Pocetna::prikaziLinijskeKomande()
{
    widgetLinijskeKomande->setVisible(true);

    this->setVisible(false);
    Dialog qd;
    qd.exec();
}

Pocetna::~Pocetna()
{
    delete ui;
}

void Pocetna::prikaziGraph() {
    widgetGraph->setVisible(true);
    this->setVisible(false);
}



