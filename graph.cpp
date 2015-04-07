#include "graph.h"
#include "ui_graph.h"

Graph::Graph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Graph),
    m_Scene(new GraphGraphicsScene)
{
    ui->setupUi(this);
    m_Scene->setParent(this);
    ui->graphicsView->setScene(m_Scene);
    ui->graphicsView->setMouseTracking(true);

    mapper = new QSignalMapper(this);

    connect(ui->state, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->state, 1);
    connect(ui->link, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->link, 2);
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(changeMode(int)));
}

Graph::~Graph() {
    delete ui;
    delete mapper;
}

void Graph::changeMode(int i) {
    /* Postavljanje moda za crtanje stanja, prelaza ili default mod */
    if(m_Scene->mode() != MODE::DEFAULT)
        m_Scene->setMode(MODE::DEFAULT);
    else
        m_Scene->setMode(MODE(i));

    /* Brise iscrtan isprekidani krug */
    m_Scene->removeLast(NULL);
}
