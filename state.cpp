#include "state.h"

int State::s_numberOfNodes = 1;

State::State(QPointF point)
    :m_center(point), m_id(s_numberOfNodes)
{
    m_circle = DRAW_SHAPE::DASHED;
    setAcceptHoverEvents(true);
    m_color = Qt::black;
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

void State::setDrawShape(DRAW_SHAPE s){
    /* metoda za postavljanje mode-a iscrtavanja */
    m_circle = s;
}

void State::addTransiton(Transition *transition) {
    transitions.push_back(transition);
}

void State::removeTransitons(Transition *transition) {
    transitions.removeOne(transition);
}

void State::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    /* nasledjena metoda za crtanje graphics item-a */
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(m_circle == DRAW_SHAPE::NORMAL) {
        /* crtanje punog kruga sa oznakom stanja */
        painter->setPen(QPen(QBrush(m_color, Qt::SolidPattern), 2));
        painter->setBrush(QBrush(Qt::white));
        setZValue(1);
        painter->drawEllipse(QPoint(0,0), 25, 25);
        QString state_id = QString::number(m_id);
        painter->drawText(QPointF(-2 - (state_id.length() - 1) * 3, 5), state_id);

    }
    else if(m_circle == DRAW_SHAPE::DASHED){
        /* iscrtavanje isprekidanog kruga */
        painter->setPen(QPen(Qt::DashLine));
        painter->drawEllipse(QPoint(0,0), 25, 25);
    }
}

QRectF State::boundingRect() const {
    /* nasledjena metoda postavljanje granicnog pravougaonika */
    return QRectF(QPointF(-25, 25), QPointF(25, -25));
}

void State::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    Q_UNUSED(mouseEvent);
    if(dynamic_cast<GraphGraphicsScene* >(this->scene())->mode() != MODE::DEFAULT) {
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
    }
    else {
        this->setFlag(QGraphicsItem::ItemIsMovable, true);
    }
}

void State::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if(mouseEvent->button() == Qt::LeftButton && dynamic_cast<GraphGraphicsScene* >(this->scene())->mode() == MODE::DELETE) {
        qDebug() << this;
        for(Transition *t : transitions) {
            t->removeSelf();
        }
        delete this;
    }
    update();
}

void State::hoverEnterEvent(QGraphicsSceneHoverEvent *hoverEvent) {
    Q_UNUSED(hoverEvent);
    m_color = Qt::red;
}

void State::hoverLeaveEvent(QGraphicsSceneHoverEvent *hoverEvent) {
    Q_UNUSED(hoverEvent);
    m_color = Qt::black;
}

QPainterPath State::shape() {
    QPainterPath path;
    path.addEllipse(this->boundingRect());
    return path;
}

