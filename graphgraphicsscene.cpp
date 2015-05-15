#include "graphgraphicsscene.h"

GraphGraphicsScene::GraphGraphicsScene(QObject *parent)
    :QGraphicsScene(parent),
     instructionLab(0)
{
    QDesktopWidget desktop;
    setSceneRect(0, 0, desktop.geometry().width(), desktop.geometry().height());
    m_mode = MODE::DEFAULT;
    lastNode = 0;
    instructionLab = InstructionLab::instance();
}

void GraphGraphicsScene::setMode(MODE mode) {
    m_mode = mode;
}

MODE GraphGraphicsScene::mode() const {
    return m_mode;
}

void GraphGraphicsScene::removeLast(State *node) {
    /* ako poslednji iscrtan isprekidani krug nije null ukluni ga sa scene i dodaj sadasnji kao poslednji */
    if(lastNode) {
        removeItem(lastNode);
        delete lastNode;
        update();
    }
    lastNode = node;
}

void GraphGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if((mouseEvent->button() == Qt::LeftButton) && (m_mode == MODE::STATE)) {
        /* on mouse press event iscrtava stanje na koordinatama kursora ako je ukljucen mod za crtanje stanja */
        node = new State(mouseEvent->scenePos());
        node->moveBy(node->center().x(), node->center().y());
        node->updateNumberOfNodes();
        node->setDrawShape(DRAW_SHAPE::NORMAL);
        addItem(node);
    }
    else if((mouseEvent->button() == Qt::LeftButton) && (m_mode == MODE::TRANSITION)) {
        /* iscrtavanje inicijalne isprekidane linije */
        transition = new Transition();
        transition->setBegin(mouseEvent->scenePos());
        transition->setEnd(mouseEvent->scenePos());

        transition->setDrawMode(DRAW_SHAPE::DASHED);
        addItem(transition);

    }

    update();
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void GraphGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if(m_mode == MODE::STATE) {
        /*
         * kada je ukljucen mod iscrtava isprekidani krug kao indikator
         * gde ce se iscrtati stanje
         */
        node = new State(mouseEvent->scenePos());
        node->moveBy(node->center().x(), node->center().y());
        node->setDrawShape(DRAW_SHAPE::DASHED);
        addItem(node);
        update();
        removeLast(node);
    }
    else if(m_mode == MODE::TRANSITION && (mouseEvent->buttons() & Qt::LeftButton)) {
        /*
         * update-uje krajnju tacku isprekidane linije
         */
        transition->setEnd(mouseEvent->scenePos());
        if(transition->collidingItems().size()) {
            for(QGraphicsItem *i : transition->collidingItems()) {
                if(dynamic_cast<State *>(i) != 0) {
                    if(!transition->from()) {
                        transition->setFrom(dynamic_cast<State* >(i));
                        break;
                    }
                }
            }
        }
    }
    update();
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void GraphGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if(m_mode == MODE::TRANSITION) {
        /*
         * postavljanje pocetnog i krajnjeg cvora i
         * promena iscravanja pune linije
         */
        bool flag = true;
        transition->setEnd(mouseEvent->scenePos());
        QList<QGraphicsItem* > items = transition->collidingItems();
        transition->setDrawMode(DRAW_SHAPE::NORMAL);
        for(QGraphicsItem *i : items) {
            if((dynamic_cast<State* >(i) != transition->from()) && (dynamic_cast<State* >(i) != 0) && (transition->from() != 0)) {
                flag = false;
                transition->setTo(dynamic_cast<State* >(i));
                instructionLab->addToInstructionlab(transition);
                transition->from()->addTransiton(transition);
                transition->to()->addTransiton(transition);
                transition->updateBegin();
                transition->updateEnd();
                break;
            }
            else {

            }
        }
        if(this->items().contains(transition) && flag) {
            removeItem(transition);
        }
    }
    update();
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

