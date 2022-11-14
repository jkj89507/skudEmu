#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->resize(600, 600);
    this->setFixedSize(600, 600);

    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    ui->graphicsView->resize(550, 550);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    scene->setSceneRect(0, 0, 550, 550);

/*    timer = new QTimer();
    connect(timer, &QTimer::timeout, &SkudItem::checkTimer);
    timer->start(1000/50)*/;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_addSkud_clicked()
{
    SkudItem*   skudItem = new SkudItem();
    skudItem->setPos(100, 100);
    scene->addItem(skudItem);
    qDebug() << "Click!";
}

