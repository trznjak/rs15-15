#include "state.h"

int State::s_numberOfNodes = 1;

State::State(QPointF point)
    :m_center(point), m_id(s_numberOfNodes)
{
    m_circle = DRAW_SHAPE::DASHED;
}

State::~State() {
//    emit updateNodeId();
}

int State::numberOfNodes() {
    return s_numberOfNodes;
}

void State::updateNumberOfNodes() {
    s_numberOfNodes++;
}

QPointF State::center() {
    return m_center;
}

void State::setDrawMode(DRAW_SHAPE s){
    /* metoda za postavljanje mode-a iscrtavanja */
    m_circle = s;
}

void State::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    /* nasledjena metoda za crtanje graphics item-a */
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(m_circle == DRAW_SHAPE::FULL || (!this->hasFocus() && (dynamic_cast<GraphGraphicsScene* >(this->scene())->mode() == MODE::DEFAULT))) {
        /* crtanje punog kruga sa oznakom stanja */
        painter->setPen(QPen(QBrush(Qt::SolidPattern), 2));
        painter->setBrush(QBrush(Qt::white));
        painter->drawEllipse(QPoint(0,0), 25, 25);
        setZValue(1);
        QString state_id = QString::number(m_id);
        painter->drawText(QPointF(-2 - (state_id.length() - 1) * 3, 5), state_id);

    }
    else if(m_circle == DRAW_SHAPE::DASHED){
        /* iscrtavanje isprekidanog kruga */
        painter->setPen(QPen(Qt::DashLine));
        painter->drawEllipse(QPoint(0,0), 25, 25);
    }
    else if(m_circle == DRAW_SHAPE::FOCUSED && (dynamic_cast<GraphGraphicsScene* >(this->scene())->mode() == MODE::DEFAULT)) {
        /* selektovan krug */
        painter->setPen(QPen(QBrush(Qt::red, Qt::SolidPattern), 2));
        painter->setBrush(QBrush(Qt::white));
        painter->drawEllipse(QPoint(0,0), 25, 25);
        setZValue(1);
        QString state_id = QString::number(m_id);
        painter->drawText(QPointF(-2 - (state_id.length() - 1) * 3, 5), state_id);
    }
}

QRectF State::boundingRect() const {
    /* nasledjena metoda postavljanje granicnog pravougaonika */
    return QRectF(QPointF(-25, 25), QPointF(25, -25));
}

void State::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if(mouseEvent->button() == Qt::LeftButton && dynamic_cast<GraphGraphicsScene* >(this->scene())->mode() == MODE::DEFAULT) {
        this->setFocus();
        this->setDrawMode(DRAW_SHAPE::FOCUSED);
    }
    if(dynamic_cast<GraphGraphicsScene* >(this->scene())->mode() != MODE::DEFAULT) {
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
        this->setFlag(QGraphicsItem::ItemIsFocusable, false);
    }
    else {
        this->setFlag(QGraphicsItem::ItemIsMovable, true);
        this->setFlag(QGraphicsItem::ItemIsFocusable, true);
    }
}

QPainterPath State::shape() {
    QPainterPath path;
    path.addEllipse(this->boundingRect());
    return path;
}

