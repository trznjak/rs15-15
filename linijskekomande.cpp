#include "linijskekomande.h"
#include "ui_linijskekomande.h"
#include<QDebug>
#include<QDialog>
#include "dialog.h"
LinijskeKomande::LinijskeKomande(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LinijskeKomande)
{
    this->setVisible(false);
    ui->setupUi(this);
    qp = new QSignalMapper;
    qp1 = new QSignalMapper;
    qp2 = new QSignalMapper;

    qp->setMapping(ui->btn1, "0");
    connect(ui->btn1, SIGNAL(clicked()), qp, SLOT(map()));
    connect(qp, SIGNAL(mapped(QString)), this, SLOT(ocisti()) );

    qp1->setMapping(ui->btn2, "0");
    connect(ui->btn2, SIGNAL(clicked()), qp1, SLOT(map()));
    connect(qp1, SIGNAL(mapped(QString)), this, SLOT(ispisi()) );

    qp2->setMapping(ui->btn3, "0");
    connect(ui->btn3, SIGNAL(clicked()), qp2, SLOT(map()));
    connect(qp2, SIGNAL(mapped(QString)), this, SLOT(obrisi()) );



//   Dialog qd;
//   qd.exec();
}

LinijskeKomande::~LinijskeKomande()
{
    delete ui;
}

void LinijskeKomande::ispisi()
{


    QString linija = ui->lineEdit->text();



   std::vector<QString> ispravne_linije; //ovde smestam ispravne linije


   //ovde za sada bojim stvari u list widgetu


       if(!linija.contains(QRegExp("Q[0-9]+ [a-z] [a-z] [D,M,L] Q[0-9]+")))
       {





           ui->lineEdit->setStyleSheet("QLineEdit {background-color: red;}");



       }
       else
       {

           QListWidgetItem *item = new QListWidgetItem(linija);
           item->setForeground(Qt::black);
           ui->listWidget->addItem(item);
           ispravne_linije.push_back(linija);

       }




}
void LinijskeKomande::ocisti()
{
    ui->lineEdit->clear();
    ui->lineEdit->setStyleSheet("QLineEdit {background-color: white;}");
}

void LinijskeKomande::obrisi()
{

}
