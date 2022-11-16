#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->resize(500, 550);
    this->setFixedSize(500, 550);

    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
//    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
//    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по вертикали
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // при установки Прямоугольника, уго верхний левый угол помещается
    // по умолчания в (0,0), поэтому точку отрисовки переносим в (-250, -250)
    scene->setSceneRect(-250, -250, 500, 500);
    scene->addLine(-250,0,250,0,QPen(Qt::red));   /// Добавляем горизонтальную линию через центр
    scene->addLine(0,250,0,-250,QPen(Qt::red));

//    timer = new QTimer();
//    connect(timer, &QTimer::timeout, );
//    timer->start(1000/50);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_addSkud_clicked()
{
    WorkItem*   workItem = new WorkItem(nullptr, 50, 50, 1);
    workItem->setPos(0, 0);
    scene->addItem(workItem);
}

void Widget::on_addSkud_2_clicked()
{
    WorkItem*   workItem = new WorkItem(nullptr, 60, 30, 2);
    workItem->setPos(0, 0);
    scene->addItem(workItem);
}

void Widget::on_addLine_clicked()
{

}

