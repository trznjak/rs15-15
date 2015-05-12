#include "instructionlab.h"

InstructionLab *InstructionLab::s_instructionLab = NULL;

InstructionLab::InstructionLab() {}

InstructionLab::~InstructionLab() {
    delete s_instructionLab;
}

void InstructionLab::addToInstructionlab(Transition *transition) {
    /* dodavanje prelaza u vektor */
    m_transitions.push_back(transition);
}

void InstructionLab::removeTransition(Transition *transition) {
    /* brisanje prelaza iz vektora */
    m_transitions.removeOne(transition);
}

const QVector<Transition* > &InstructionLab::transitions() {
    return m_transitions;
}

InstructionLab* InstructionLab::instance() {
    /* klasa singelton */
    if(!s_instructionLab)
        s_instructionLab = new InstructionLab();
    return s_instructionLab;
}

