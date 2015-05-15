#include "graph.h"
#include "ui_graph.h"

Graph::Graph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Graph),
    m_scene(new GraphGraphicsScene)
{
    ui->setupUi(this);
    this->setVisible(false);
    m_scene->setParent(this);
    ui->graphicsView->setScene(m_scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing, true);
    ui->graphicsView->setMouseTracking(true);

    mapper = new QSignalMapper(this);

    QPixmap pixmap0(":/hand.png");
    QIcon buttonIcon0(pixmap0);
    ui->defaultButton->setIcon(buttonIcon0);
    ui->defaultButton->setIconSize(QSize(30, 30));
    QPixmap pixmap1(":/circle.png");
    QIcon buttonIcon1(pixmap1);
    ui->stateButton->setIcon(buttonIcon1);
    ui->stateButton->setIconSize(QSize(30, 30));
    QPixmap pixmap2(":/line.png");
    QIcon buttonIcon2(pixmap2);
    ui->transitionButton->setIcon(buttonIcon2);
    ui->transitionButton->setIconSize(QSize(30, 30));
    QPixmap pixmap3(":/delete.png");
    QIcon buttonIcon(pixmap3);
    ui->deleteButton->setIcon(buttonIcon);
    ui->deleteButton->setIconSize(QSize(30, 30));

    connect(ui->deleteButton, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->deleteButton, MODE::DELETE);
    connect(ui->stateButton, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->stateButton, MODE::STATE);
    connect(ui->transitionButton, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->transitionButton, MODE::TRANSITION);
    connect(ui->defaultButton, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->defaultButton, MODE::DEFAULT);
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(changeMode(int)));

    group.addButton(ui->deleteButton);
    group.addButton(ui->stateButton);
    group.addButton(ui->transitionButton);
    group.addButton(ui->defaultButton);

    ui->defaultButton->click();
}

Graph::~Graph() {
    delete ui;
    delete mapper;
    delete m_scene;
}

void Graph::changeMode(int m) {
    /*
     * Brise iscrtan isprekidani krug
     * kada se promeni mod
     */
    if(m_scene->mode() == MODE::STATE && m != MODE::STATE) {
        m_scene->removeLast(0);
    }

    /* Postavljanje moda za crtanje stanja, prelaza ili default mod */
    m_scene->setMode(MODE(m));

}
