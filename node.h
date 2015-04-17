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

class Node : public QGraphicsItem {

public:
    Node(QPointF point, GraphGraphicsScene *scene);
    ~Node();

    static int numberOfNodes();
    static void updateNumberOfNodes();

    void setDrawMode(DRAW_SHAPE);

signals:
    void updateNodeId();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:
    QPointF m_Center;
    int m_Id;
    static int s_numberOfNodes;

    DRAW_SHAPE m_Circle;

    GraphGraphicsScene *m_Scene;
};



#endif // NODE_H
