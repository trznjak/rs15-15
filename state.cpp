#include "state.h"

int State::s_numberOfNodes = 1;

State::State(QPointF point, GraphGraphicsScene *scene)
    :m_center(point), m_id(s_numberOfNodes), m_scene(scene)
{
    m_circle = DRAW_SHAPE::DASHED;
}

State::State(State &state)
    :m_center(state.m_center),
     m_id(state.m_id),
     s_numberOfNodes(state.s_numberOfNodes),
     m_circle(state.m_circle),
     m_scene(state.m_scene)
{}

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

State &State::operator =(State &state) {
    State temp(state);
    std::swap(temp.m_center, m_center);
    std::swap(temp.m_id, m_id);
    std::swap(temp.s_numberOfNodes, s_numberOfNodes);
    std::swap(temp.m_circle, m_circle);
    std::swap(temp.m_scene, m_scene);

    return *this;
}

void State::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    /* nasledjena metoda za crtanje graphics item-a */
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(m_circle == DRAW_SHAPE::FULL || (!this->hasFocus() && (m_scene->mode() == MODE::DEFAULT))) {
        /* crtanje punog kruga sa oznakom stanja */
        painter->setPen(QPen(QBrush(Qt::SolidPattern), 2));
        painter->setBrush(QBrush(Qt::white));
        painter->drawEllipse(m_center, 25, 25);
        setZValue(1);
        QString state_id = QString::number(m_id);
        painter->drawText(QPointF(m_center.x() - 2 - (state_id.length() - 1) * 3, m_center.y() + 5), state_id);
    }
    else if(m_circle == DRAW_SHAPE::DASHED){
        /* iscrtavanje isprekidanog kruga */
        painter->setPen(QPen(Qt::DashLine));
        painter->drawEllipse(m_center, 25, 25);
    }
    else if(m_circle == DRAW_SHAPE::FOCUSED) {
        /* selektovan krug */
        painter->setPen(QPen(Qt::blue, Qt::SolidLine));
        painter->drawEllipse(m_center, 25, 25);
        QString state_id = QString::number(m_id);
        painter->drawText(QPointF(m_center.x() - 2 - (state_id.length() - 1) * 3, m_center.y() + 5), state_id);
    }
}

QRectF State::boundingRect() const {
    /* nasledjena metoda postavljanje granicnog pravougaonika */
    return QRectF(QPointF(m_center.x() - 25, m_center.y() + 25), QPointF(m_center.x() + 25, m_center.y() - 25));
}

void State::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if(mouseEvent->button() == Qt::LeftButton && m_scene->mode() == MODE::DEFAULT) {
        this->setFocus();
        this->setDrawMode(DRAW_SHAPE::FOCUSED);
    }
    if(m_scene->mode() != MODE::DEFAULT) {
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

