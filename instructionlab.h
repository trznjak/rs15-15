#ifndef INSTRUCTIONLAB_H
#define INSTRUCTIONLAB_H

#include <QVector>
#include <QString>

#include "transition.h"

class InstructionLab {
public:
    ~InstructionLab();
    void addToInstructionlab(Transition *);
    static InstructionLab* instance();

private:
    InstructionLab();
    QVector<Transition* > m_Transitions;
    QVector<QString > m_Instructions;
    static InstructionLab *s_InstructionLab;
};

#endif // INSTRUCTIONLAB_H
