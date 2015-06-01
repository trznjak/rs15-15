#include "transition.h"


Transition::Transition() {
    m_from = 0;
    m_to = 0;
    setAcceptHoverEvents(true);
    instructionLab = InstructionLab::instance();
    m_color = Qt::black;
    m_flag = false;
    QGraphicsItem::setFlag(QGraphicsItem::ItemIsFocusable);

    ti = new TransitionInstruction(this);
    QObject::connect(ti, SIGNAL(accepted()), this, SLOT(snimiInstrukcije()));

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

DRAW_SHAPE Transition::drawMode() {
    return m_line;
}

void Transition::removeSelf() {
    instructionLab->removeTransition(this);
    m_to->removeTransitons(this);
    m_from->removeTransitons(this);
    //dynamic_cast<GraphGraphicsScene* >(this->scene())->removeItem(this);
    delete this;
}

void Transition::setFlag(bool f) {
    m_flag = f;
    m_center = m_from->pos();
    m_angle = 0;
    QGraphicsItem::setFlag(QGraphicsItem::ItemIsMovable);
    QGraphicsItem::setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

void Transition::snimiInstrukcije() {
    instructions = ti->instructions();
    QGraphicsItem::update();
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

        if(!m_flag) {
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
            QPointF temp = c;
            painter->setPen(QPen(QColor(Qt::darkGreen)));
            int i = 1;
            for(QString s : instructions) {
                painter->drawText(temp, s);
                temp.setY(c.y() - (i++) * 15);
            }
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
        else {
            painter->setPen(QPen(QColor(Qt::darkGreen), 1));
            QPointF center = QPointF(m_from->pos().x() + (50 * cos(m_angle)), m_from->pos().y() + (50 * sin(m_angle)));
            QLineF line = QLineF(m_from->pos(), center);
            line.setLength(line.length() * 2 + 10);
            QPointF textPoint = line.p2();
            int i = 1;
            for(QString s : instructions) {
                painter->drawText(textPoint, s);
                textPoint.setY(textPoint.y() + (i++) * 12);
            }
            painter->setPen(QPen(QBrush(m_color, Qt::SolidPattern), 1));
            painter->drawEllipse(center, 50, 50);
        }

    }
}

void Transition::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    /* double click kada je u stisnuto default stanju otvara se dialog */
    if(mouseEvent->button() == Qt::LeftButton && dynamic_cast<GraphGraphicsScene* >(this->scene())->mode() == MODE::DEFAULT) {

        ti->exec();
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

QVariant Transition::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) {
    if(change == QGraphicsItem::ItemPositionChange && this->scene()) {
        m_angle = (m_angle + 0.1) >= 360 ? 0 : (m_angle + 0.1);
        return QPointF(cos(m_angle), sin(m_angle));
    }
    return QGraphicsItem::itemChange(change, value);
}

QRectF Transition::boundingRect() const {
    if(m_flag)
        return QRectF(QPoint(m_from->pos().x() - 50 + (50 * cos(-m_angle)), m_from->pos().y() + 50 + (50 * sin(m_angle))),
                      QPoint(m_from->pos().x() + 50 + (50 * cos(m_angle)), m_from->pos().y() - 50 - (50 * sin(-m_angle))));
    else
        return QRectF(QPoint(m_begin.x(), m_begin.y() + 1), QPoint(m_end.x(), m_end.y() - 1));
}

QPainterPath Transition::shape() const {
    QPainterPath path;

    if(m_flag) {
        QPointF center = QPointF(m_from->pos().x() + (50 * cos(m_angle)), m_from->pos().y() + (50 * sin(m_angle)));
        path.addEllipse(center, 50, 50);
    }
    else {
        /* malo cudan poligon za shape :D */
        QPolygonF polygon;
        polygon << QPointF(m_begin.x(), m_begin.y() + 10);
        polygon << controlPoint(m_begin, m_end, 30);
        polygon << QPointF(m_end.x(), m_end.y() + 10);
        polygon << QPointF(m_end.x(), m_end.y() - 17);
        polygon << controlPoint(m_begin, m_end, 0);
        polygon << QPointF(m_begin.x(), m_begin.y() - 17);
        path.addPolygon(polygon);
    }
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

QString &Transition::ispis() {
    QString *string = new QString;
    for(QString s : instructions) {
        string->append(QString("Q%1 %2 Q%3\n").arg(from()->id()).arg(s).arg(to()->id()));
    }
    return *string;
}
