#ifndef INSTRUCTIONLAB_H
#define INSTRUCTIONLAB_H

#include <QVector>
#include <QString>

#include "transition.h"
#include "state.h"

class State;

class InstructionLab {
public:
    ~InstructionLab();
    void addToInstructionlab(State *);
    const QVector<State* >& states();
    static InstructionLab* instance();


private:
    InstructionLab();
    QVector<State* > m_states;
    static InstructionLab *s_instructionLab;
};

#endif // INSTRUCTIONLAB_H
