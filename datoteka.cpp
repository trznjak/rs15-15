#include "datoteka.h"
#include "ui_datoteka.h"
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>

Datoteka::Datoteka(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Datoteka)
{
    ui->setupUi(this);
    this->setVisible(false);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(ucitaj()));
}

void Datoteka::ucitaj()
{
    flag = false;
    ui->listWidget->clear();
    instructions.clear();

//    QFileDialog dialog(this);
//    dialog.setFileMode(QFileDialog::AnyFile);

     QString fileName = QFileDialog::getOpenFileName(this,
        tr("Izaberite datoteku"), "/home", tr("Text files (*.txt)"));



    QTextStream in(&fileName);

    while(!in.atEnd()) {
        QString line = in.readLine();

        if(!line.contains(QRegExp("Q[0-9]+ [a-z] [a-z] [R,S,L] Q[0-9]+")))
        {

            QListWidgetItem *item = new QListWidgetItem(line, ui->listWidget);
            item->setForeground(Qt::red); // sets red text
            item->setBackground(Qt::white);

            ui->listWidget->addItem(item);
            ui->listWidget->show();

            flag = true;
        }
        else
        {
            QListWidgetItem *item = new QListWidgetItem(line, ui->listWidget);
            instructions.push_back(line);
            item->setForeground(Qt::black);
            ui->listWidget->addItem(item);
        }
    }

    if(!flag) {
        emit upaliNext();
    }
    else {
        emit losaKomanda();
    }

    instructionLab->setVectorInstruction(instructions);


}

Datoteka::~Datoteka()
{
    delete ui;
}
