#ifndef INSTRUCTIONLAB_H
#define INSTRUCTIONLAB_H

#include <QVector>
#include <QString>
#include <mainwindow.h>
#include <QObject>
#include <QDebug>

#include "transition.h"
#include "state.h"

class State;
class Transition;

class InstructionLab : public QObject {

    Q_OBJECT

public:
    ~InstructionLab();
    void addToInstructionlab(Transition *);
    void removeTransition(Transition *);
    const QVector<Transition* >& transitions();
    static InstructionLab* instance();

public slots:
    void fromGraphToString();


private:
    InstructionLab();
    QVector<Transition* > m_transitions;
    QVector<QString > m_instructionsAsString;
    static InstructionLab *s_instructionLab;
    QWidget *parent;
};

#endif // INSTRUCTIONLAB_H
