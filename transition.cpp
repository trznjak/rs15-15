#include "transition.h"

Transition::Transition() {
    m_from = 0;
    m_to = 0;
    setAcceptHoverEvents(true);
    instructionLab = InstructionLab::instance();
    m_color = Qt::black;

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
    if(m_to != 0) updateBegin();
}

State *Transition::from() {
    return m_from;
}

void Transition::setTo(State *to) {
    m_to = to;
    if(m_from != 0) updateEnd();
}

State *Transition::to() {
    return m_to;
}

void Transition::setDrawMode(DRAW_SHAPE s) {
    m_line = s;
}

void Transition::removeSelf() {
    instructionLab->removeTransition(this);
    m_to->removeTransitons(this);
    m_from->removeTransitons(this);
    dynamic_cast<GraphGraphicsScene* >(this->scene())->removeItem(this);
    delete this;
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

        painter->setPen(QPen(QBrush(m_color, Qt::SolidPattern), 2));

        /*
         * Postavljanje pocetne i krajnje tacke
         * da budu na rubovima kruga
         */
        QLineF tempLine = QLineF(m_end, m_begin);
        tempLine.setLength(25);
        m_end = tempLine.p2();

        tempLine = QLineF(m_begin, m_end);
        tempLine.setLength(25);
        m_begin = tempLine.p2();

        QPointF c = controlPoint(m_begin, m_end, 40);
        painter->setPen(QPen(QColor(Qt::darkGreen)));
        painter->drawText(c, "o, z, D");
        c.setY(c.y() + 12);
        painter->drawText(c, "d, v, L");
        painter->setPen(QPen(QColor(m_color)));


        /* crtanje linije */
        QPainterPath path = QPainterPath(m_begin);
        path.quadTo(c, m_end);
        painter->drawPath(path);

        /* crtanje strelice */
        QLineF line = QLineF(m_begin, m_end);
        QLineF arrowl = QLineF(m_end, m_begin);
        QLineF arrowr = QLineF(m_end, m_begin);
        arrowl.setAngle(line.angle() - 30 + 180);
        arrowr.setAngle(line.angle() + 10 + 180);
        arrowl.setLength(25);
        arrowr.setLength(25);
        painter->drawLine(arrowl);
        painter->drawLine(arrowr);

        updateBegin();
        updateEnd();
    }
}

void Transition::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    /* double click kada je u stisnuto default stanju otvara se dialog */
    if(mouseEvent->button() == Qt::LeftButton && dynamic_cast<GraphGraphicsScene* >(this->scene())->mode() == MODE::DEFAULT) {
        TransitionInstruction ti(this);
        ti.exec();
    }

    /* double click kada je stisnuto delete brise se ta grana */
    if(mouseEvent->button() == Qt::LeftButton && dynamic_cast<GraphGraphicsScene* >(this->scene())->mode() == MODE::DELETE) {
        removeSelf();
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

    /* malo cudan poligon za shape :D */
    QPolygonF polygon;
    polygon << QPointF(m_begin.x(), m_begin.y() + 10);
    polygon << controlPoint(m_begin, m_end, 30);
    polygon << QPointF(m_end.x(), m_end.y() + 10);
    polygon << QPointF(m_end.x(), m_end.y() - 17);
    polygon << controlPoint(m_begin, m_end, 0);
    polygon << QPointF(m_begin.x(), m_begin.y() - 17);
    path.addPolygon(polygon);
    return path;
}

QPointF Transition::controlPoint(QPointF begin, QPointF end, int length) const {
    /* pravljenje kontrolne tacke za bezierovu krivu */
    QLineF l = QLineF(begin, end);
    l.setLength(l.length() / 2);
    QLineF l1 = QLineF(l.p2(), l.p1());
    l1.setAngle(l.angle() + 90);
    l1.setLength(length);
    return l1.p2();
}
