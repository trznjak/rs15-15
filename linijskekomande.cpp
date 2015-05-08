#include "linijskekomande.h"
#include "ui_linijskekomande.h"

LinijskeKomande::LinijskeKomande(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LinijskeKomande)
{
    ui->setupUi(this);
    qp = new QSignalMapper;
    qp1 = new QSignalMapper;

    qp->setMapping(ui->btn1, "0");
    connect(ui->btn1, SIGNAL(clicked()), qp, SLOT(map()));
    connect(qp, SIGNAL(mapped(QString)), this, SLOT(ispisi()) );


    qp1->setMapping(ui->Uputstvo, "0");
    connect(ui->Uputstvo, SIGNAL(clicked()), qp1, SLOT(map()));
    connect(qp1, SIGNAL(mapped(QString)), this, SLOT(prikaziUputstvo()) );

    ui->listWidget->setVisible(false);
    ui->l->setVisible(false);
}

LinijskeKomande::~LinijskeKomande()
{
    delete ui;
}

void LinijskeKomande::ispisi()
{
    QString text = ui->txt1->toPlainText();

    //Ovde smestam redove
    QStringList listaStringova;
    //ovde smestam reci svakog reda
    QStringList reci;
   listaStringova=text.split("\n");
//   std::cout << listaStringova.length() << std::endl;

   std::vector<QString> linije;
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
           item->setBackground(Qt::white); // sets green background


           ui->listWidget->addItem(item);


           ui->listWidget->show();
       }
       else
       {
           QListWidgetItem *item = new QListWidgetItem("Uspesno unesena linija!!! :-)");
           ui->listWidget->addItem(item);
       }

   }
}

void LinijskeKomande::prikaziUputstvo()
{
    ui->l->setVisible(true);
    QListWidgetItem *item = new QListWidgetItem("Prvo unesete stanje Q pa bilo \n"
                                                "koji broj (npr Q16) pa zatim\n"
                                                "unesete razmak pa posle razmaka jedan\n"
                                                "karakter pa zatim ponovo razmak \n"
                                                "pa zatim drugi karakter\n"
                                                "pa zatim L ili D ili M(levo desno\n ili ostajete \n"
                                                "na tom mestu) pa zatim opet razmak\n i na kraju stanje u koje \n"
                                                "zelite da predjete(isto kao i\n prvo stanje koje\n"
                                                "ste uneli npr q21).Pravilan unos\n bi bio Q1 p r D Q2.\n"
                                                "Srecno :-)");
    ui->l->addItem(item);

}
