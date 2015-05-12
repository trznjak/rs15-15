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

signals:
    void updateNodeId();

private:
    QPointF m_center;
    int m_id;
    static int s_numberOfNodes;

    QList<Transition* > transitions;

    DRAW_SHAPE m_circle;
    Qt::GlobalColor m_color;

};



#endif // NODE_H
