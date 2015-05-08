#include "transition.h"

Transition::Transition() {
    m_from = 0;
    m_to = 0;
    setAcceptHoverEvents(true);
}

Transition::~Transition() {

}

void Transition::setBegin(QPointF begin) {
    m_begin = begin;
}

void Transition::updateBegin() {
    m_begin = m_from->pos();
}

QPointF Transition::begin() const {
    return m_begin;
}

void Transition::setEnd(QPointF end) {
    m_end = end;
}

void Transition::updateEnd() {
    m_end = m_to->pos();
}
QPointF Transition::end() const {
    return m_end;
}

void Transition::setFrom(State *from) {
    m_from = from;
    qDebug() << "setFrom" << m_from;
    if(m_to != 0) updateBegin();
}

State *Transition::from() {
    return m_from;
}

void Transition::setTo(State *to) {
    m_to = to;
    qDebug() << "setTo" << m_to;
    if(m_from != 0) updateEnd();
}

void Transition::setDrawMode(DRAW_SHAPE s) {
    m_line = s;
}


void Transition::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    /* nasledjena metoda za crtanje graphics item-a */
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(m_line == DRAW_SHAPE::DASHED) {
        painter->setPen(QPen(Qt::DashLine));
        painter->drawLine(m_begin, m_end);


    }
    else if(m_line == DRAW_SHAPE::NORMAL) {

        if(dynamic_cast<GraphGraphicsScene* >(this->scene())->mode() == MODE::DEFAULT) {
            painter->setPen(QPen(QBrush(m_color, Qt::SolidPattern), 2));
        }
        else {
            painter->setPen(QPen(QBrush(Qt::black, Qt::SolidPattern), 2));
        }

        QLineF tempLine = QLineF(m_end, m_begin);
        tempLine.setLength(25);
        m_end = tempLine.p2();

        /* crtanje linije */
        QLineF line = QLineF(m_begin, m_end);
        painter->drawLine(line);

        /* crtanje strelice */
        QLineF arrowl = QLineF(m_end, m_begin);
        QLineF arrowr = QLineF(m_end, m_begin);
        arrowl.setAngle(line.angle() - 20 + 180);
        arrowr.setAngle(line.angle() + 20 + 180);
        arrowl.setLength(25);
        arrowr.setLength(25);
        painter->drawLine(arrowl);
        painter->drawLine(arrowr);

        updateBegin();
        updateEnd();
    }
}

void Transition::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if(mouseEvent->button() == Qt::LeftButton && dynamic_cast<GraphGraphicsScene* >(this->scene())->mode() == MODE::DEFAULT) {
        TransitionInstruction ti;
        ti.exec();
    }
}

void Transition::hoverEnterEvent(QGraphicsSceneHoverEvent *hoverEvent) {
    Q_UNUSED(hoverEvent);
    m_color = Qt::red;
}

void Transition::hoverLeaveEvent(QGraphicsSceneHoverEvent *hoverEvent) {
    Q_UNUSED(hoverEvent);
    m_color = Qt::black;
}

QRectF Transition::boundingRect() const {
    return QRectF(QPoint(m_begin.x(), m_begin.y() + 1), QPoint(m_end.x(), m_end.y() - 1));
}

QPainterPath Transition::shape() const {
    QPainterPath path;

//    path.moveTo(m_begin);
//    path.lineTo(m_end);

    QPolygonF polygon;
    polygon << QPointF(m_begin.x(), m_begin.y() + 5);
    polygon << QPointF(m_begin.x(), m_begin.y() - 5);
    polygon << QPointF(m_end.x(), m_end.y() - 5);
    polygon << QPointF(m_end.x(), m_end.y() + 5);
    path.addPolygon(polygon);
    return path;
}
