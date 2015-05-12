#include "transitioninstruction.h"
#include "ui_transitioninstruction.h"

TransitionInstruction::TransitionInstruction(Transition *caller) :
    QDialog(0),
    ui(new Ui::TransitionInstruction),
    m_caller(caller)
{
    ui->setupUi(this);
    qDebug() << m_caller;
}

TransitionInstruction::~TransitionInstruction()
{
    delete ui;
}
