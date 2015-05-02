#include "transition.h"

Transition::Transition(GraphGraphicsScene *scene)
    :m_scene(scene)
{

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
