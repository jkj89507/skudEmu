#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->resize(500, 550);
    this->setFixedSize(500, 550);

    scene = new MyScene(this);
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

    modeName = "";
    counterClick = 0;
    connect(scene, &MyScene::signal_clickRelesed, this, &Widget::slot_readClick);
    connect(scene, &MyScene::signal_clickRelesed, this, &Widget::slot_encreseCounter);

//    timer = new QTimer();
//    connect(timer, &QTimer::timeout, );
//    timer->start(1000/50);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::slot_readClick()
{
    listPoints = scene->getLastClickResultsList();
    for (int index = 0; index < listPoints.length(); ++index) {
        qInfo() << index << " "
                << "X: " << listPoints[index]["X"]
                << "Y: " << listPoints[index]["Y"];
    }
    if (listPoints.length() > 10) {
        listPoints.clear();
        scene->clearClickResultsList();
    }
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
    modeName = "Line";
}

void Widget::slot_encreseCounter()
{
    counterClick++;
    if (counterClick == 2 && modeName.endsWith("Line")) {
        QPainter painter(this);
        painter.setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::FlatCap));
        qreal x1 = listPoints[listPoints.length()-2]["X"];
        qreal y1 = listPoints[listPoints.length()-2]["Y"];
        qreal x2 = listPoints[listPoints.length()-1]["X"];
        qreal y2 = listPoints[listPoints.length()-1]["Y"];
        painter.drawLine(0, 0, 200, 200);
    }
}
