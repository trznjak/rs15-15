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

class GraphGraphicsScene;

class State : public QGraphicsItem {

public:
    State(QPointF point);
    ~State();

    static int numberOfNodes();
    static void updateNumberOfNodes();

    QPointF center();
    void setDrawMode(DRAW_SHAPE s);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    QPainterPath shape();

signals:
    void updateNodeId();

private:
    QPointF m_center;
    int m_id;
    static int s_numberOfNodes;

    DRAW_SHAPE m_circle;

};



#endif // NODE_H
