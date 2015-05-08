#include "graph.h"
#include "ui_graph.h"

Graph::Graph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Graph),
    m_scene(new GraphGraphicsScene)
{
    ui->setupUi(this);
    m_scene->setParent(this);
    ui->graphicsView->setScene(m_scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing, true);
    ui->graphicsView->setMouseTracking(true);

    mapper = new QSignalMapper(this);

    connect(ui->state, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->state, 1);
    connect(ui->link, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->link, 2);
    connect(ui->defaultButton, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->defaultButton, 0);
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(changeMode(int)));

    group.addButton(ui->state);
    group.addButton(ui->link);
    group.addButton(ui->defaultButton);

    ui->defaultButton->click();
}

Graph::~Graph() {
    delete ui;
    delete mapper;
    delete m_scene;
}

void Graph::changeMode(int i) {
    /*
     * Brise iscrtan isprekidani krug
     * kada se promeni mod
     */
    if(m_scene->mode() == MODE::STATE && MODE(i) != MODE::STATE) {
        m_scene->removeLast(0);
    }

    /* Postavljanje moda za crtanje stanja, prelaza ili default mod */
    m_scene->setMode(MODE(i));

}
