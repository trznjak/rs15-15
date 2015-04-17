#include "graphgraphicsscene.h"

GraphGraphicsScene::GraphGraphicsScene(QObject *parent)
    :QGraphicsScene(parent)
{
    setSceneRect(0, 0, 700, 500);
    m_Mode = MODE::DEFAULT;
    lastNode = 0;
}

void GraphGraphicsScene::setMode(MODE mode) {
    m_Mode = mode;
}

MODE GraphGraphicsScene::mode() const {
    return m_Mode;
}

void GraphGraphicsScene::removeLast(Node *node) {
    /* ako poslednji iscrtan isprekidani krug nije null ukluni ga sa scene i dodaj sadasnji kao poslednji */
    if(lastNode) {
        removeItem(lastNode);
        update();
    }
    if(node != 0)
        lastNode = node;
}

void GraphGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    /* on mouse press event iscrtava stanje na koordinatama kursora ako je ukljucen mod za crtanje stanja */
    if((mouseEvent->button() == Qt::LeftButton) && (m_Mode == MODE::STATE)) {
        Node *node = new Node(mouseEvent->scenePos(), this);
        node->updateNumberOfNodes();
        node->setDrawMode(DRAW_SHAPE::FULL);
        addItem(node);
    }
    update();
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void GraphGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    /* kada je ukljucen mod iscrtava isprekidani krug kao indikator gde ce se iscrtati stanje */
    Node *node;
    if(m_Mode == MODE::STATE) {
        node = new Node(mouseEvent->scenePos(), this);
        node->setDrawMode(DRAW_SHAPE::DASHED);
        addItem(node);
        update();
        removeLast(node);
    }
    update();
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void GraphGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    update();
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

