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
    /* on mouse press event iscrtava stanje na koordinatama kursora ako je ukljucen mod za crtanje stanja */
    if((mouseEvent->button() == Qt::LeftButton) && (m_mode == MODE::STATE)) {
        node = new State(mouseEvent->scenePos());
        node->moveBy(node->center().x(), node->center().y());
        node->updateNumberOfNodes();
        node->setDrawMode(DRAW_SHAPE::FULL);
        addItem(node);
        //instructionLab->addToInstructionlab(node);
    }
    else if((mouseEvent->button() == Qt::LeftButton) && (m_mode == MODE::TRANSITION)) {
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
    /* kada je ukljucen mod iscrtava isprekidani krug kao indikator gde ce se iscrtati stanje */
    if(m_mode == MODE::STATE) {
        node = new State(mouseEvent->scenePos());
        node->moveBy(node->center().x(), node->center().y());
        node->setDrawMode(DRAW_SHAPE::DASHED);
        addItem(node);
        update();
        removeLast(node);
    }
    else if(m_mode == MODE::TRANSITION && (mouseEvent->buttons() & Qt::LeftButton)) {
        transition->setEnd(mouseEvent->scenePos());
    }
    update();
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void GraphGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if(m_mode == MODE::TRANSITION) {
        transition->setEnd(mouseEvent->scenePos());
        transition->setDrawMode(DRAW_SHAPE::FULL);
        QList<QGraphicsItem* > items = transition->collidingItems();
        if(items.size() == 2) {
            transition->setFrom(dynamic_cast<State* >(items[0]));
            transition->setTo(dynamic_cast<State* >(items[1]));
        }
    }
    update();
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

