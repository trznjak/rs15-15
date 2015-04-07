#include "instructionlab.h"

InstructionLab *InstructionLab::s_InstructionLab = NULL;

InstructionLab::InstructionLab() {}

InstructionLab::~InstructionLab() {
    /* brisanje prelaza */
    for(QVector<Transition* >::iterator i = m_Transitions.begin(); i != m_Transitions.end(); i++) {
        delete *i;
    }
}

void InstructionLab::addToInstructionlab(Transition *transition) {
    /* dodavanje prelaza u vektor */
    m_Transitions.push_back(transition);
}

InstructionLab* InstructionLab::instance() {
    /* klasa singelton */
    if(!s_InstructionLab)
        s_InstructionLab = new InstructionLab();
    return s_InstructionLab;
}

