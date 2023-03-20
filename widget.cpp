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
    scene = new MyScene(this);
    scene->clear();
    QString path = "C:/Qt/workplace/skudEmu/wall.jpg"; // path to background image
    QPixmap backgroundImage(path);
    QBrush backgroundBrush(backgroundImage);
    scene->setBackgroundBrush(backgroundBrush);

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setRenderHint(QPainter::SmoothPixmapTransform);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по вертикали
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->drawWorkplace();

    amountOfItemsInRow = (sceneSizeWidth - 10) / 40;
    for (int rowIndex = 10; rowIndex < sceneSizeHeight; rowIndex += 40) {
        for (int columnIndex = 10; columnIndex < sceneSizeWidth; columnIndex += 40) {
            WorkItem* tempWorkItem = new WorkItem(nullptr, "Active_" + QString::number(getNumberOfWorkItem("Active_")), 10, 10, 3, false);
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
    WorkItem*   workItem = new WorkItem(nullptr, "Skud_1" + QString::number(getNumberOfWorkItem("Skud_1")), 50, 50, 1);
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
    qInfo() << "counterClick: " << counterClick << "mode name: " << modeName;
    if (counterClick == 2 && modeName.endsWith("Line")) {
        qreal x1 = listLastConnectors[listLastConnectors.length()-2]->getPositionItem()["X"];
        qreal y1 = listLastConnectors[listLastConnectors.length()-2]->getPositionItem()["Y"];
        qreal x2 = listLastConnectors[listLastConnectors.length()-1]->getPositionItem()["X"];
        qreal y2 = listLastConnectors[listLastConnectors.length()-1]->getPositionItem()["Y"];
        listLastConnectors[listLastConnectors.length()-2]->setMyNeighbour(listLastConnectors[listLastConnectors.length()-1]);
//        connect(listLastConnectors[listLastConnectors.length()-2], &ConnItem::sentMessage,
//                listLastConnectors[listLastConnectors.length()-1], &ConnItem::getMessageForSent);
        listLastConnectors[listLastConnectors.length()-1]->setMyNeighbour(listLastConnectors[listLastConnectors.length()-2]);
        listLastConnectors.clear();
        this->paintLine(x1, y1, x2, y2);
        modeName = "Choose";
    }
}

void Widget::slot_update_spendTime()
{
    spendsSeconds++;
//    qInfo() << spendsSeconds << "s";
}

void Widget::getItem(WorkItem* workItem)
{
    saveLastClickItem = workItem;
    modeName = "Choose";
}

void Widget::getConnItem(ConnItem* connItem)
{
    saveLastClickItem = connItem;
    if (saveLastClickItem->getName().contains("Connector")) {
        listLastConnectors.append(connItem);
        modeName = "Line";
    } else {
        modeName = "Choose";
    }
}

void Widget::setActiveItem(WorkItem* item)
{
    if (modeName.endsWith("Choose") && listAllItems.indexOf(saveLastClickItem) != -1)
    {
        int lastClickItemIndex = listAllItems.indexOf(saveLastClickItem);
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

int Widget::getNumberOfWorkItem(QString searchElement)
{
    int number = 0;
    if (listAllItems.length() != 0) {
        for (int i = 0; i < listAllItems.length(); i++) {
            if (listAllItems[i]->getName().contains(searchElement)) {
                number++;
            }
        }
    }
    return number;
}

void Widget::setConnectorsPoint(WorkItem* item)
{
    //TODO: изсенит проверяемые границы в ряде.
    // Баг: при установке в активную точку элемента в конце ряда -
    // устанавливает коннектор в начале следующего ряда
    int currentIndexItem = this->getNumberItemFromList(item);
    item->setBuffer(new Buffer());
    connect(item, &WorkItem::sentMessage, item->getBuffer(), &Buffer::getAccessToSendMessage);
    if (currentIndexItem - amountOfItemsInRow >= 0) {
        WorkItem* temp = listAllItems[currentIndexItem - amountOfItemsInRow];
        disconnect(temp, &WorkItem::sentItem, this, &Widget::getItem);
        ConnItem* connectorItem = new ConnItem(nullptr, "Connector_" + item->getName() + "Up",
                                               10, 10,
                                               4, false);
        connect(item->getBuffer(), &Buffer::sentMessageToConnItem, connectorItem, &ConnItem::getMessageForSent);
        connect(connectorItem, &ConnItem::sentConnItem, this, &Widget::getConnItem);
        connectorItem->setMyOwnerWorkItem(item);
        connectorItem->setPos(temp->x(), temp->y());
        listAllItems[currentIndexItem - amountOfItemsInRow] = connectorItem;
        scene->addItem(connectorItem);
    }
    if (currentIndexItem + amountOfItemsInRow <= listAllItems.length()) {
        WorkItem* temp = listAllItems[currentIndexItem + amountOfItemsInRow];
        disconnect(temp, &WorkItem::sentItem, this, &Widget::getItem);
        ConnItem* connectorItem = new ConnItem(nullptr, "Connector_" + item->getName() + "Down",
                                               10, 10,
                                               4, false);
        connect(item->getBuffer(), &Buffer::sentMessageToConnItem, connectorItem, &ConnItem::getMessageForSent);
        connect(connectorItem, &ConnItem::sentConnItem, this, &Widget::getConnItem);
        connectorItem->setMyOwnerWorkItem(item);
        connectorItem->setPos(temp->x(), temp->y());
        listAllItems[currentIndexItem + amountOfItemsInRow] = connectorItem;
        scene->addItem(connectorItem);
    }
    if (currentIndexItem - 1 >= 0) {
        WorkItem* temp = listAllItems[currentIndexItem - 1];
        disconnect(temp, &WorkItem::sentItem, this, &Widget::getItem);
        ConnItem* connectorItem = new ConnItem(nullptr, "Connector_" + item->getName() + "Left",
                                               10, 10,
                                               4, false);
        connect(item->getBuffer(), &Buffer::sentMessageToConnItem, connectorItem, &ConnItem::getMessageForSent);
        connect(connectorItem, &ConnItem::sentConnItem, this, &Widget::getConnItem);
        connectorItem->setMyOwnerWorkItem(item);
        connectorItem->setPos(temp->x(), temp->y());
        listAllItems[currentIndexItem - 1] = connectorItem;
        scene->addItem(connectorItem);
    }
    if (currentIndexItem + 1 <= listAllItems.length()) {
        WorkItem* temp = listAllItems[currentIndexItem + 1];
        disconnect(temp, &WorkItem::sentItem, this, &Widget::getItem);
        ConnItem* connectorItem = new ConnItem(nullptr, "Connector_" + item->getName() + "Right",
                                               10, 10,
                                               4, false);
        connect(item->getBuffer(), &Buffer::sentMessageToConnItem, connectorItem, &ConnItem::getMessageForSent);
        connect(connectorItem, &ConnItem::sentConnItem, this, &Widget::getConnItem);
        connectorItem->setMyOwnerWorkItem(item);;
        connectorItem->setPos(temp->x(), temp->y());
        listAllItems[currentIndexItem + 1] = connectorItem;
        scene->addItem(connectorItem);
    }
}

void Widget::paintLine(qreal x1_coord, qreal y1_coord,
                       qreal x2_coord, qreal y2_coord)
{
    int width = qFabs(x2_coord - x1_coord);
    int height = qFabs(y2_coord - y1_coord);
    WorkItem *lineItem;
    if (width >= height) {
        lineItem = new WorkItem(nullptr, "Line_" + QString::number(getNumberOfWorkItem("Line")),
                                width, 6,
                                0);
        lineItem->setPos(x1_coord + width/2, y1_coord);
        if (x1_coord >= x2_coord) {
            lineItem->setTransform(QTransform().translate((width) * -1, 0));
        }
    } else {
        lineItem = new WorkItem(nullptr, "Line_" + QString::number(getNumberOfWorkItem("Line")),
                                6, height,
                                0);
        lineItem->setPos(x1_coord, y1_coord + height/2);
        if (y1_coord >= y2_coord) {
            lineItem->setTransform(QTransform().translate(0, (height) * -1));
        }
    }
    modeName = "";
    counterClick = 0;
    listPoints.clear();
    qInfo() << "set mode: empty";
    listAllItems.append(lineItem);
    scene->addItem(lineItem);
    this->redraw();
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
    for (int y = 10; y < sceneSizeHeight; y += 40) {
        scene->addLine(10, y, sceneSizeWidth - 40, y, QPen(Qt::black));
    }
    for (int x = 10; x < sceneSizeWidth; x += 40) {
        scene->addLine(x, 10, x, sceneSizeHeight - 40,QPen(Qt::black));
    }
}

void Widget::redraw()
{
    scene->update();
}
