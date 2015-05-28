#include "transitioninstruction.h"
#include "ui_transitioninstruction.h"

TransitionInstruction::TransitionInstruction(Transition *caller) :
    QDialog(0),
    ui(new Ui::TransitionInstruction),
    m_caller(caller)
{
    ui->setupUi(this);

    ui->lineEdit->setMaxLength(1);
    ui->lineEdit->setPlaceholderText("Karakter");
    ui->lineEdit_2->setMaxLength(1);
    ui->lineEdit_2->setPlaceholderText("Karakter");
    ui->lineEdit_3->setMaxLength(1);
    ui->lineEdit_3->setPlaceholderText("R ili L");
    QRegExp rx ("[R|L]");
    ui->lineEdit_3->setValidator(new QRegExpValidator(rx, this));
    ui->listWidget->setSelectionMode(QAbstractItemView::SingleSelection);



}

TransitionInstruction::~TransitionInstruction() {
    delete ui;
}

QVector<QString> &TransitionInstruction::instructions() {
    return m_instructions;
}


void TransitionInstruction::on_add_clicked() {
    QString string = QString("%1 %2 %3").arg(ui->lineEdit->text()).arg(ui->lineEdit_2->text()).arg(ui->lineEdit_3->text());
    m_instructions.push_back(string);
    ui->listWidget->addItem(string);
}

void TransitionInstruction::on_delete_2_clicked() {
    qDebug() << ui->listWidget->selectedItems().first();
    ui->listWidget->removeItemWidget(ui->listWidget->selectedItems().first());
}
