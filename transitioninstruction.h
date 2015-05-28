#ifndef TRANSITIONINSTRUCTION_H
#define TRANSITIONINSTRUCTION_H

#include <QDialog>
#include <QDebug>
#include <QString>
#include <QVector>

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

    QVector<QString> &instructions();

private slots:
    void on_add_clicked();
    void on_delete_2_clicked();

private:
    Ui::TransitionInstruction *ui;

    QVector<QString > m_instructions;



    Transition *m_caller;
};

#endif // TRANSITIONINSTRUCTION_H
