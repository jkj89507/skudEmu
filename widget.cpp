#include "widget.h"
#include "ui_widget.h"
#include "connItem.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    /*Init scene*/

    ui->setupUi(this);
    listAllItems.clear();

    this->resize(700, 700);
    this->setFixedSize(700, 700);

    scene = new MyScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0, 0, sceneSize, sceneSize);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по вертикали
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->drawWorkplace();

    amountOfItemsInRow = (sceneSize - 10) / 40;
    for (int rowIndex = 10; rowIndex < sceneSize; rowIndex += 40) {
        for (int columnIndex = 10; columnIndex < sceneSize; columnIndex += 40) {
            WorkItem* tempWorkItem = new WorkItem(nullptr, "Active", 10, 10, 3, false);
            tempWorkItem->setPos(columnIndex, rowIndex);
            listAllItems.append(tempWorkItem);
            connect(tempWorkItem, &WorkItem::sentItem, this, &Widget::getItem);
            scene->addItem(tempWorkItem);
        }
    }

    modeName = "";
    counterClick = 0;
    spendsSeconds = 0;
    timer = new QTimer();
    connect(scene, &MyScene::signal_clickRelesed, this, &Widget::slot_readClick);
    connect(scene, &MyScene::signal_clickRelesed, this, &Widget::slot_encreseCounter);
    connect(timer, &QTimer::timeout, this, &Widget::slot_update_listItems);
    connect(timer, &QTimer::timeout, this, &Widget::slot_update_spendTime);
    timer->start(1000);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::slot_readClick()
{
    listPoints = scene->getLastClickResultsList();
    if (listPoints.length() > 10) {
        listPoints.clear();
        scene->clearClickResultsList();
    }
}

void Widget::on_addSkud_clicked()
{

    WorkItem*   workItem = new WorkItem(nullptr, "Skud_1", 50, 50, 1);
    this->setActiveItem(workItem);
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

//    if (counterClick == 2 && modeName.endsWith("Line")) {
//        qreal x1 = listPoints[listPoints.length()-2]["X"];
//        qreal y1 = listPoints[listPoints.length()-2]["Y"];
//        qreal x2 = listPoints[listPoints.length()-1]["X"];
//        qreal y2 = listPoints[listPoints.length()-1]["Y"];
//        this->paintLine(x1, y1, x2, y2);
//    }
}

void Widget::slot_update_listItems()
{
//    if (listAllItems.size() > 0) {
//        for (int i = 0; i < listAllItems.size(); i++) {
//            qInfo() << listAllItems[i]->toolTip();
//        }
//    } else {
//        qInfo() << "No items";
//    }
//    qInfo() << "================" << this->getTime() << "================";
}

void Widget::slot_update_spendTime()
{
    spendsSeconds++;
//    qInfo() << spendsSeconds << "s";
}

//void Widget::slot_update_checkConnect()
//{
//    if (listAllItems.size() > 0) {
//            for (int i = 0; i < listAllItems.size(); i++) {
//                qInfo() << listAllItems[i];
//            }
//        } else {
//            qInfo() << "No items";
//        }
////    qInfo() << "================" << this->getTime() << "================";
//}

void Widget::getItem(WorkItem* workItem)
{
    saveLastCkickItem = workItem;
    modeName = "Choose";
}

void Widget::setActiveItem(WorkItem* item)
{
    if (modeName.endsWith("Choose") && listAllItems.indexOf(saveLastCkickItem) != -1)
    {
        int lastClickItemIndex = listAllItems.indexOf(saveLastCkickItem);
        WorkItem* temp = listAllItems[lastClickItemIndex];
        this->redraw();
        item->setPos(temp->x(), temp->y());
        listAllItems[lastClickItemIndex] = item;
        this->setConnectorsPoint(item);
        scene->addItem(item);
    } else {
        listAllItems.append(item);
        item->setPos(0, 0);
        scene->addItem(item);
    }
}

int Widget::getNumberItemFromList(WorkItem* item)
{
   for (int keyItem = 0; keyItem < listAllItems.length(); keyItem++) {
       if (listAllItems[keyItem] == item) {
           return keyItem;
       }
   }
   return -1;
}

void Widget::setConnectorsPoint(WorkItem* item)
{
    //TODO: изсенит проверяемые границы в ряде.
    // Баг: при установке в активную точку элемента в конце ряда -
    // устанавливает коннектор в начале следующего ряда
    int currentIndexItem = this->getNumberItemFromList(item);
    if (currentIndexItem - amountOfItemsInRow >= 0) {
        WorkItem* temp = listAllItems[currentIndexItem - amountOfItemsInRow];
        ConnItem* connectorItem = new ConnItem(nullptr, "Connector", 10, 10, 4, false);
        connectorItem->setMyOwnerWorkItem(item);
        connectorItem->setPos(temp->x(), temp->y());
        listAllItems[currentIndexItem - amountOfItemsInRow] = connectorItem;
        scene->addItem(connectorItem);
    }
    if (currentIndexItem + amountOfItemsInRow <= listAllItems.length()) {
        WorkItem* temp = listAllItems[currentIndexItem + amountOfItemsInRow];
        ConnItem* connectorItem = new ConnItem(nullptr, "Connector", 10, 10, 4, false);
        connectorItem->setMyOwnerWorkItem(item);
        connectorItem->setPos(temp->x(), temp->y());
        listAllItems[currentIndexItem + amountOfItemsInRow] = connectorItem;
        scene->addItem(connectorItem);
    }
    if (currentIndexItem - 1 >= 0) {
        WorkItem* temp = listAllItems[currentIndexItem - 1];
        ConnItem* connectorItem = new ConnItem(nullptr, "Connector", 10, 10, 4, false);
        connectorItem->setMyOwnerWorkItem(item);
        connectorItem->setPos(temp->x(), temp->y());
        listAllItems[currentIndexItem - 1] = connectorItem;
        scene->addItem(connectorItem);
    }
    if (currentIndexItem + 1 <= listAllItems.length()) {
        WorkItem* temp = listAllItems[currentIndexItem + 1];
        ConnItem* connectorItem = new ConnItem(nullptr, "Connector", 10, 10, 4, false);
        connectorItem->setMyOwnerWorkItem(item);;
        connectorItem->setPos(temp->x(), temp->y());
        listAllItems[currentIndexItem + 1] = connectorItem;
        scene->addItem(connectorItem);
    }
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

void Widget::drawWorkplace()
{
    /*Draw lines*/
    for (int x = 10; x < 650; x+=40) {
        scene->addLine(x,10,x,sceneSize - 40,QPen(Qt::black));
        scene->addLine(10,x,sceneSize - 40,x,QPen(Qt::black));
    }
}

void Widget::redraw()
{
    scene->update();
//    scene->clear();
//    this->drawWorkplace();
//    for (auto i : listAllItems) {
//        scene->addItem(i);
//    }
}
