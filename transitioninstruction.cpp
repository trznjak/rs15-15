#include "transitioninstruction.h"
#include "ui_transitioninstruction.h"

TransitionInstruction::TransitionInstruction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransitionInstruction)
{
    ui->setupUi(this);
}

TransitionInstruction::~TransitionInstruction()
{
    delete ui;
}
