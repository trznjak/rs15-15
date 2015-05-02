#include "instructionlab.h"

InstructionLab *InstructionLab::s_instructionLab = NULL;

InstructionLab::InstructionLab() {}

InstructionLab::~InstructionLab() {
    delete s_instructionLab;
}

void InstructionLab::addToInstructionlab(State *state) {
    /* dodavanje prelaza u vektor */
    m_states.push_back(state);
}

const QVector<State* > &InstructionLab::states() {
    return m_states;
}

InstructionLab* InstructionLab::instance() {
    /* klasa singelton */
    if(!s_instructionLab)
        s_instructionLab = new InstructionLab();
    return s_instructionLab;
}

