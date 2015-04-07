#include "node.h"

int Node::s_numberOfNodes = 1;

Node::Node(QPointF point, GraphGraphicsScene *scene)
    :m_Center(point), m_Id(s_numberOfNodes), m_Scene(scene)
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable);

    m_Circle = DRAW_CIRCLE::DASHED;
}

Node::~Node() {
//    emit updateNodeId();
}

int Node::numberOfNodes() {
    return s_numberOfNodes;
}

void Node::updateNumberOfNodes() {
    s_numberOfNodes++;
}

void Node::setDrawMode(DRAW_CIRCLE b){
    /* metoda za postavljanje mode-a iscrtavanja */
    m_Circle = b;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    /* nasledjena metoda za crtanje graphics item-a */
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(m_Circle == DRAW_CIRCLE::FULL) {
        /* crtanje punog kruga sa oznakom stanja */
        painter->setPen(QPen(Qt::SolidLine));
        painter->drawEllipse(m_Center, 25, 25);
        QString state_id = QString::number(m_Id);
        painter->drawText(QPointF(m_Center.x() - 2 - (state_id.length() - 1) * 3, m_Center.y() + 5), state_id);
    }
    else if(m_Circle == DRAW_CIRCLE::DASHED){
        /* iscrtavanje isprekidanog kruga */
        painter->setPen(QPen(Qt::DashLine));
        painter->drawEllipse(m_Center, 25, 25);
    }
    else if(m_Circle == DRAW_CIRCLE::SELECTED) {
        /* selektovan krug */
        painter->setPen(QPen(Qt::blue, Qt::SolidLine));
        painter->drawEllipse(m_Center, 25, 25);
        QString state_id = QString::number(m_Id);
        painter->drawText(QPointF(m_Center.x() - 2 - (state_id.length() - 1) * 3, m_Center.y() + 5), state_id);
        this->setSelected(true);
    }
}

QRectF Node::boundingRect() const {
    /* nasledjena metoda postavljanje granicnog pravougaonika */
    return QRectF(QPointF(m_Center.x() - 25, m_Center.y() + 25), QPointF(m_Center.x() + 25, m_Center.y() - 25));
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if(mouseEvent->button() == Qt::LeftButton && m_Scene->mode() == MODE::DEFAULT) {
        if(!this->isSelected()) {
            this->setSelected(true);
            this->setDrawMode(DRAW_CIRCLE::SELECTED);
            qDebug() << "SELECTED: false";
        }
        else {
            this->setSelected(false);
            this->setDrawMode(DRAW_CIRCLE::FULL);
            qDebug() << "SELECTED: true";
        }

    }
}

