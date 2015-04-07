#ifndef GRAPHGRAPHICSSCENE_H
#define GRAPHGRAPHICSSCENE_H

#include "node.h"
#include "enumeration.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QObject>

class Node;

class GraphGraphicsScene : public QGraphicsScene {

public:
    GraphGraphicsScene(QObject *parent = 0);

    void setMode(MODE);
    MODE mode() const;

public slots:
    void removeLast(Node *node);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:
    MODE m_Mode;

    Node *lastNode;
};

#endif // GRAPHGRAPHICSSCENE_H
