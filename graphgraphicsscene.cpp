#include "graphgraphicsscene.h"

GraphGraphicsScene::GraphGraphicsScene(QObject *parent)
    :QGraphicsScene(parent),
     instructionLab(0)
{
    setSceneRect(0, 0, 700, 500);
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
         * i postavlja pocetni cvor da se ocuva smer iscrtavanja
         */
        for(QGraphicsItem *i : transition->collidingItems()) {
            if(dynamic_cast<State *>(i) != 0) {
                qDebug() << "mouseMove" << dynamic_cast<State* >(i);
                transition->setFrom(dynamic_cast<State* >(i));
                break;
            }
        }
        transition->setEnd(mouseEvent->scenePos());
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
        transition->setEnd(mouseEvent->scenePos());
        QList<QGraphicsItem* > items = transition->collidingItems();
        if(items.size() >= 2) {
            transition->setDrawMode(DRAW_SHAPE::NORMAL);
            for(QGraphicsItem *i : items) {
                if((dynamic_cast<State *>(i) != transition->from()) && (dynamic_cast<State *>(i) != 0)) {
                    transition->setTo(dynamic_cast<State *>(i));
                    break;
                }
            }

            transition->updateBegin();
            transition->updateEnd();
        }
        else {
            removeItem(transition);
        }
    }
    update();
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

