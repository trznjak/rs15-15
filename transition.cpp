#include "transition.h"

Transition::Transition(GraphGraphicsScene *scene)
    :m_scene(scene)
{

}

Transition::Transition(Transition &transition) {
    m_from = transition.m_from;
    m_to = transition.m_to;
    m_begin = transition.m_begin;
    m_end = transition.m_end;
    m_arrowDirection = transition.m_arrowDirection;
    m_line = transition.m_line;
    m_scene = transition.m_scene;
}

Transition::~Transition() {

}

void Transition::setBegin(QPointF begin) {
    m_begin = begin;
}

QPointF Transition::begin() const {
    return m_begin;
}

void Transition::setEnd(QPointF end) {
    m_end = end;
}

QPointF Transition::end() const {
    return m_end;
}

void Transition::setDrawMode(DRAW_SHAPE s) {
    m_line = s;
}

void Transition::setArrowDirecion(QPointF ad) {
    m_arrowDirection = ad;
}

Transition &Transition::operator =(Transition &transition) {
    Transition temp(transition);
    std::swap(m_from, temp.m_from);
    std::swap(m_to, temp.m_to);
    std::swap(m_begin, temp.m_begin);
    std::swap(m_end, temp.m_end);
    std::swap(m_arrowDirection, temp.m_arrowDirection);
    std::swap(m_line, temp.m_line);
    std::swap(m_scene, temp.m_scene);
}

void Transition::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    /* nasledjena metoda za crtanje graphics item-a */
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(m_line == DRAW_SHAPE::DASHED) {
        painter->setPen(QPen(Qt::DashLine));
        painter->drawLine(m_begin, m_end);
    }
    else if(m_line == DRAW_SHAPE::FULL) {
        painter->setPen(QPen(QBrush(Qt::SolidPattern), 2));
        painter->drawLine(m_begin, m_end);

    }
}

QRectF Transition::boundingRect() const {
    return QRectF(QPoint(m_begin.x(), m_begin.y() + 1), QPoint(m_end.x(), m_end.y() - 1));
}

QPainterPath Transition::shape() const {
    QPainterPath path;
    path.moveTo(m_begin);
    path.lineTo(m_end);
    return path;
}
