#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QPointF>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

#include "enumeration.h"
#include "graphgraphicsscene.h"
#include "transition.h"

enum TIP {
    POCETNO = 1,
    KRAJNJE = 2,
};

class GraphGraphicsScene;
class Transition;

class State : public QGraphicsItem {

public:
    State(QPointF point);
    ~State();

    static int numberOfNodes();
    static void updateNumberOfNodes();

    QPointF center();
    void setDrawShape(DRAW_SHAPE s);
    int id();

    /* !!!!! TODO: dodati da se stave pocetno i kranje stanje !!!!!!!!*/
    void setTipStanja(TIP t);

    void addTransiton(Transition *);
    void removeTransitons(Transition *);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *hoverEvent);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *hoverEvent);
    QPainterPath shape();

private:
    QPointF m_center;
    int m_id;
    TIP m_tipStanja;
    static int s_numberOfNodes;

    QList<Transition* > m_transitions;

    DRAW_SHAPE m_circle;
    Qt::GlobalColor m_color;

    InstructionLab *instructionLab;

    void updateStateId(int id);

};



#endif // NODE_H
