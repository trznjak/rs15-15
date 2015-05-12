#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->textEdit->setText("Prvo unesete stanje Q pa bilo \n"
                          "koji broj (npr Q16) pa zatim\n"
                          "unesete razmak pa posle razmaka jedan\n"
                          "karakter pa zatim ponovo razmak \n"
                          "pa zatim drugi karakter\n"
                          "pa zatim L ili D ili M(levo desno\n ili ostajete \n"
                          "na tom mestu) pa zatim opet razmak\n i na kraju stanje u koje \n"
                          "zelite da predjete(isto kao i\n prvo stanje koje\n"
                          "ste uneli npr q21).Pravilan unos\n bi bio Q1 p r D Q2.\n"
                          "Srecno :-)");

   ui->textEdit->setTextColor(QColor(Qt::green));
}

Dialog::~Dialog()
{
    delete ui;
}
