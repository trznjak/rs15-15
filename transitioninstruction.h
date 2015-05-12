#ifndef TRANSITIONINSTRUCTION_H
#define TRANSITIONINSTRUCTION_H

#include <QDialog>
#include <QDebug>
#include <QList>
#include <QString>

#include "transition.h"

class Transition;

namespace Ui {
class TransitionInstruction;
}

class TransitionInstruction : public QDialog {
    Q_OBJECT

public:
    explicit TransitionInstruction(Transition *);
    ~TransitionInstruction();

private:
    Ui::TransitionInstruction *ui;

    QList<QString > instructions;

    Transition *m_caller;
};

#endif // TRANSITIONINSTRUCTION_H
