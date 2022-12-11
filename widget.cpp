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
    spendsSeconds = 0;
    timer = new QTimer();
    connect(scene, &MyScene::signal_clickRelesed, this, &Widget::slot_readClick);
    connect(scene, &MyScene::signal_clickRelesed, this, &Widget::slot_encreseCounter);
    connect(timer, &QTimer::timeout, this, &Widget::slot_update_listItems);
    connect(timer, &QTimer::timeout, this, &Widget::slot_update_spendTime);
    timer->start(1000);

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
//        qInfo() << index << " "
//                << "X: " << listPoints[index]["X"]
//                << "Y: " << listPoints[index]["Y"];
    }
    if (listPoints.length() > 10) {
        listPoints.clear();
        scene->clearClickResultsList();
    }
}

void Widget::on_addSkud_clicked()
{
    WorkItem*   workItem = new WorkItem(nullptr, "Skud_1", 50, 50, 1);
    listAllItems.append(workItem);
    workItem->setPos(0, 0);
    scene->addItem(workItem);
}

void Widget::on_addSkud_2_clicked()
{
    WorkItem*   workItem = new WorkItem(nullptr, "Skud_2", 60, 30, 2);
    listAllItems.append(workItem);
    workItem->setPos(0, 0);
    scene->addItem(workItem);
}

void Widget::on_addLine_clicked()
{
    modeName = "Line";
    counterClick = 0;
    listPoints.clear();
    qInfo() << "set mode: line";
}

void Widget::slot_encreseCounter()
{
    counterClick++;
    qInfo() << "counterClick: " << counterClick;

    if (counterClick == 2 && modeName.endsWith("Line")) {
        qreal x1 = listPoints[listPoints.length()-2]["X"];
        qreal y1 = listPoints[listPoints.length()-2]["Y"];
        qreal x2 = listPoints[listPoints.length()-1]["X"];
        qreal y2 = listPoints[listPoints.length()-1]["Y"];
        this->paintLine(x1, y1, x2, y2);
    }
}

void Widget::slot_update_listItems()
{
    if (listAllItems.size() > 0) {
        for (int i = 0; i < listAllItems.size(); i++) {
            qInfo() << listAllItems[i]->toolTip();
        }
    } else {
        qInfo() << "No items";
    }
    qInfo() << "================" << this->getTime() << "================";
}

void Widget::slot_update_spendTime()
{
    spendsSeconds++;
    qInfo() << spendsSeconds << "s";
}

void Widget::paintLine(qreal x1_coord, qreal y1_coord,
                       qreal x2_coord, qreal y2_coord)
{
    int width = qFabs(x2_coord - x1_coord);
    int height = qFabs(y2_coord - y1_coord);
    int agileRotateGrad = -90 + qSin(width/height)/(3.14/180);
    WorkItem *lineItem;
    if (width >= height) {
        lineItem = new WorkItem(nullptr, "Line", width, 6, 0);
        lineItem->setPos(x1_coord + width/2, y1_coord + 3);
        lineItem->setTransform(QTransform().translate(x1_coord - width/2, y1_coord)
                                            .rotate(agileRotateGrad)
                                            .translate(-1 * (x1_coord - width/2), -1 * y1_coord));
    } else {
        lineItem = new WorkItem(nullptr, "Line", 6, height, 0);
        lineItem->setPos(x1_coord + 3, y1_coord + height/2);
        lineItem->setTransform(QTransform().translate(x1_coord, y1_coord - height/2)
                                            .rotate(agileRotateGrad)
                                            .translate(-1 * x1_coord , -1 * (y1_coord - height/2)));
    }
    modeName = "";
    counterClick = 0;
    listPoints.clear();
    qInfo() << "set mode: empty";
    listAllItems.append(lineItem);
    scene->addItem(lineItem);
}

QString Widget::getTime()
{
    int sec = spendsSeconds % 60;
    int min = floor(spendsSeconds / 60);
    int hours = floor(spendsSeconds / 3600);
    QString result = "";
    if (hours < 10) {
        result += "0" + QString::number(hours) + ":";
    } else {
        result += QString::number(hours) + ":";
    }
    if (min < 10) {
        result += "0" + QString::number(min) + ":";
    } else {
        result += QString::number(min) + ":";
    }
    if (sec < 10) {
        result += "0" + QString::number(sec);
    } else {
        result += QString::number(sec);
    }
    return result;
}
