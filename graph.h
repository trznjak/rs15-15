#ifndef GRAPH_H
#define GRAPH_H

#include "graphgraphicsscene.h"
#include "node.h"
#include "instructionlab.h"
#include "enumeration.h"

#include <QWidget>
#include <QSignalMapper>

class GraphGraphicsScene;

namespace Ui {
class Graph;
}

class Graph : public QWidget {
    Q_OBJECT

public:
    explicit Graph(QWidget *parent = 0);
    ~Graph();

public slots:
    void changeMode(int);

private:
    Ui::Graph *ui;

    GraphGraphicsScene *m_Scene;
    QSignalMapper *mapper;

};

#endif // GRAPH_H
