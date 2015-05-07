#ifndef TRANSITIONINSTRUCTION_H
#define TRANSITIONINSTRUCTION_H

#include <QDialog>

namespace Ui {
class TransitionInstruction;
}

class TransitionInstruction : public QDialog
{
    Q_OBJECT

public:
    explicit TransitionInstruction(QWidget *parent = 0);
    ~TransitionInstruction();

private:
    Ui::TransitionInstruction *ui;
};

#endif // TRANSITIONINSTRUCTION_H
