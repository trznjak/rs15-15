#include "instructionlab.h"

InstructionLab *InstructionLab::s_instructionLab = NULL;

InstructionLab::InstructionLab() {}

InstructionLab::~InstructionLab() {
    delete s_instructionLab;
}

void InstructionLab::addToInstructionlab(Transition *transition) {
    /* dodavanje prelaza u vektor */
    m_states.push_back(transition);
}

const QVector<Transition* > &InstructionLab::transitions() {
    return m_states;
}

InstructionLab* InstructionLab::instance() {
    /* klasa singelton */
    if(!s_instructionLab)
        s_instructionLab = new InstructionLab();
    return s_instructionLab;
}

