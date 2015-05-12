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

    qp->setMapping(ui->btn1, "0");
    connect(ui->btn1, SIGNAL(clicked()), qp, SLOT(map()));
    connect(qp, SIGNAL(mapped(QString)), this, SLOT(ispisi()) );



    ui->listWidget->setVisible(false);


//   Dialog qd;
//   qd.exec();
}

LinijskeKomande::~LinijskeKomande()
{
    delete ui;
}

void LinijskeKomande::ispisi()
{
    ui->listWidget->clear();
    QString text = ui->txt1->toPlainText();


    //Ovde smestam redove
    QStringList listaStringova;
    //ovde smestam reci svakog reda
    QStringList reci;
   listaStringova=text.split("\n");
//   std::cout << listaStringova.length() << std::endl;

   std::vector<QString> linije;
   std::vector<QString> ispravne_linije; //ovde smestam ispravne linije
   for(int i=0; i<listaStringova.length();i++)
   {
       linije.push_back(listaStringova[i]);



   }


   //ovde za sada bojim stvari u list widgetu
   for(int i=0; i<linije.size();i++)
   {

       ui->listWidget->setVisible(true);
       if(!linije[i].contains(QRegExp("Q[0-9]+ [a-z] [a-z] [D,M,L] Q[0-9]+")))
       {
           QListWidgetItem *item = new QListWidgetItem(linije[i]);

           item->setForeground(Qt::red); // sets red text
           item->setBackground(Qt::white);


           ui->listWidget->addItem(item);


           ui->listWidget->show();
       }
       else
       {

           QListWidgetItem *item = new QListWidgetItem(linije[i]);
           item->setForeground(Qt::black);
           ui->listWidget->addItem(item);
           ispravne_linije.push_back(linije[i]);

       }

   }

//   for(int j=0;j<ispravne_linije.size();j++)
//       qDebug() << ispravne_linije[j];
}

