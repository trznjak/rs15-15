#ifndef INSTRUCTIONLAB_H
#define INSTRUCTIONLAB_H

#include <QVector>
#include <QString>

#include "transition.h"
#include "state.h"

class State;
class Transition;

class InstructionLab {
public:
    ~InstructionLab();
    void addToInstructionlab(Transition *);
    const QVector<Transition* >& transitions();
    static InstructionLab* instance();


private:
    InstructionLab();
    QVector<Transition* > m_states;
    static InstructionLab *s_instructionLab;
};

#endif // INSTRUCTIONLAB_H
