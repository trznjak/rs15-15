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

    QFile file("komande.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();

        if(!line.contains(QRegExp("Q[0-9]+ [a-z] [a-z] [D,M,L] Q[0-9]+")))
        {

            QListWidgetItem *item = new QListWidgetItem(line, ui->listWidget);
            item->setForeground(Qt::red); // sets red text
            item->setBackground(Qt::white);

            ui->listWidget->addItem(item);
            ui->listWidget->show();
        }
        else
        {
            QListWidgetItem *item = new QListWidgetItem(line, ui->listWidget);
            item->setForeground(Qt::black);
            ui->listWidget->addItem(item);

        }
    }

    file.close();
}

Datoteka::~Datoteka()
{
    delete ui;
}
