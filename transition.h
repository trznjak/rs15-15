#ifndef TRANSITION_H
#define TRANSITION_H

#include <QRect>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsItem>

#include "state.h"
#include "enumeration.h"

class GraphGraphicsScene;
class State;

class Transition : public QGraphicsItem {
public:
    Transition(GraphGraphicsScene *scene);
    Transition(Transition &transition);
    ~Transition();

    void setBegin(QPointF begin);
    QPointF begin() const;
    void setEnd(QPointF end);
    QPointF end() const;
    void setDrawMode(DRAW_SHAPE m);
    void setArrowDirecion(QPointF ad);

    Transition& operator =(Transition& transition);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QPainterPath shape() const;

private:
    State *m_from; // cvor od koga krece linija
    State *m_to; // cvor do koga ide linija

    QPointF m_begin; // pocetak za isprekidanu liniju
    QPointF m_end; // kraj za isprekidanu liniju
    QPointF m_arrowDirection;
    DRAW_SHAPE m_line;
    GraphGraphicsScene *m_scene;
};

#endif // TRANSITION_H
