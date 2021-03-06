#include "state.h"

int State::s_numberOfNodes = 0;

State::State(QPointF point)
    :m_center(point), m_id(s_numberOfNodes)
{
    m_circle = DRAW_SHAPE::DASHED;
    setAcceptHoverEvents(true);
    m_color = Qt::black;
    QGraphicsItem::setZValue(1);
    m_tipStanja = TIP(0);
    instructionLab = InstructionLab::instance();
}

State::~State() {
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

int State::id() {
    return m_id;
}

void State::setTipStanja(TIP t) {
    m_tipStanja = t;
}

void State::addTransiton(Transition *transition) {
    m_transitions.push_back(transition);
}

void State::removeTransitons(Transition *transition) {
    m_transitions.removeOne(transition);
}

void State::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    /* nasledjena metoda za crtanje graphics item-a */
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(m_circle == DRAW_SHAPE::NORMAL) {
        /* crtanje punog kruga sa oznakom stanja */
        painter->setPen(QPen(QBrush(m_color, Qt::SolidPattern), 2));
        painter->setBrush(QBrush(Qt::white));
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
        for(Transition *t : m_transitions) {
            t->removeSelf();

        }
        updateStateId(this->m_id);
        delete this;
    }
    else if(mouseEvent->button() == Qt::LeftButton && dynamic_cast<GraphGraphicsScene* >(this->scene())->mode() == MODE::TRANSITION) {
        Transition *transition = new Transition();
        transition->setFrom(this);
        transition->setTo(this);
        transition->setDrawMode(DRAW_SHAPE::NORMAL);
        transition->setFlag(true);
        this->scene()->addItem(transition);
        this->addTransiton(transition);
        instructionLab->addToInstructionlab(transition);
    }
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

void State::updateStateId(int id) {
    for(QGraphicsItem *i : dynamic_cast<GraphGraphicsScene* >(this->scene())->items()) {
        if(id < dynamic_cast<State* >(i)->m_id) dynamic_cast<State* >(i)->m_id--;
    }
    s_numberOfNodes--;
}

