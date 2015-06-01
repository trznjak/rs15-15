#include "datoteka.h"
#include "ui_datoteka.h"
#include <QFile>
#include <QMessageBox>
#include <QDebug>

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

    QFile file("komande.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);

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

    file.close();
}

Datoteka::~Datoteka()
{
    delete ui;
}
