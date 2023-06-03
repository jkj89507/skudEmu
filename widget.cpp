#include "widget.h"

#include "ui_widget.h"

Widget::Widget(QWidget * parent): QWidget(parent), ui(new Ui::Widget) {
    /*Init scene*/

    ui -> setupUi(this);
    listAllItems.clear();
    scene = new MyScene(this);
    scene -> clear();

    QPixmap backgroundImage("C:/Users/JKJ89507/Desktop/workplace/5.2kurs/diplom/skudEmu/images/wall.jpg");
    QBrush backgroundBrush(backgroundImage);
    scene -> setBackgroundBrush(backgroundBrush);

    QPixmap addSkudBackground("C:/Users/JKJ89507/Desktop/workplace/5.2kurs/diplom/skudEmu/images/skud.png");
    ui -> addSkud -> setIcon((QIcon) addSkudBackground);

    QPixmap addZoneBackground("C:/Users/JKJ89507/Desktop/workplace/5.2kurs/diplom/skudEmu/images/zone.png");
    ui -> addZone -> setIcon((QIcon) addZoneBackground);

    QPixmap addLineBackground("C:/Users/JKJ89507/Desktop/workplace/5.2kurs/diplom/skudEmu/images/line.png");
    ui -> addLine -> setIcon((QIcon) addLineBackground);

    QPixmap addDbBackground("C:/Users/JKJ89507/Desktop/workplace/5.2kurs/diplom/skudEmu/images/database.png");
    ui -> addDb -> setIcon((QIcon) addDbBackground);

    QPixmap addCrmBackground("C:/Users/JKJ89507/Desktop/workplace/5.2kurs/diplom/skudEmu/images/crm.png");
    ui -> addCrm -> setIcon((QIcon) addCrmBackground);

    ui -> graphicsView -> setRenderHint(QPainter::Antialiasing);
    ui -> graphicsView -> setRenderHint(QPainter::SmoothPixmapTransform);
    ui -> graphicsView -> setScene(scene);
    ui -> graphicsView -> setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по вертикали
    ui -> graphicsView -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    Utils::drawWorkplace(scene, sceneSizeWidth, sceneSizeHeight);

    amountOfItemsInRow = (sceneSizeWidth - 10) / 40;
    for (int rowIndex = 10; rowIndex < sceneSizeHeight; rowIndex += 40) {
        for (int columnIndex = 10; columnIndex < sceneSizeWidth; columnIndex += 40) {
            WorkItem * tempWorkItem = new WorkItem(nullptr, "Active_" + QString::number(getNumberOfWorkItem("Active_")), 10, 10, 3, false);
            tempWorkItem -> setPos(columnIndex, rowIndex);
            listAllItems.append(tempWorkItem);
            connect(tempWorkItem, & WorkItem::sentItem, this, & Widget::getItem);
            scene -> addItem(tempWorkItem);
        }
    }

    modeName = "";
    counterClick = 0;
    spendsSeconds = 0;
    timer = new QTimer();
    connect(scene, & MyScene::signal_clickRelesed, this, & Widget::slot_readClick);
    connect(scene, & MyScene::signal_clickRelesed, this, & Widget::slot_encreseCounter);
    connect(timer, & QTimer::timeout, this, & Widget::slot_update_spendTime);
    timer -> start(1000);
}

Widget::~Widget() {
    delete ui;
}

void Widget::slot_readClick() {
    listPoints = scene -> getLastClickResultsList();
    if (listPoints.length() > 10) {
        listPoints.clear();
        scene -> clearClickResultsList();
    }
}

void Widget::getMapConnector(QMap < QString, bool > mapConnector) {
    this -> mapConnector = mapConnector;
}

void Widget::on_addSkud_clicked() {
    this -> updateMapConnector();
    this -> addSkud();
}

void Widget::on_addCrm_clicked() {
    this -> updateMapConnector();
    this -> addCrm();
}

void Widget::on_addDb_clicked() {
    this -> updateMapConnector();
    this -> addDb();
}

void Widget::on_addZone_clicked() {
    this -> updateMapConnector();
    this -> addSkud();

    modeName = "Zone";
    counterClick = 0;
    listPoints.clear();
    qInfo() << "set mode: zone";
}

void Widget::on_addLine_clicked() {
    modeName = "Line";
    counterClick = 0;
    listPoints.clear();
    qInfo() << "set mode: line";
}

void Widget::on_setPropertyButton_clicked() {
    agent = new Agent();
    agent->levelAccess = ui -> spinBox -> value();
    agent->name = ui -> nameTextField -> toPlainText();
}

void Widget::updateMapConnector() {
    connDialog = new ConnectorDialog(this);
    connect(connDialog, & ConnectorDialog::sentMapConnector, this, & Widget::getMapConnector);
    connDialog -> exec();
}

void Widget::slot_encreseCounter() {
    counterClick++;
    qInfo() << "counterClick: " << counterClick << "mode name: " << modeName;
    if (counterClick == 2 && modeName.contains("Line")) {
        qreal x1 = listLastConnectors[listLastConnectors.length() - 2] -> getPositionItem()["X"];
        qreal y1 = listLastConnectors[listLastConnectors.length() - 2] -> getPositionItem()["Y"];
        qreal x2 = listLastConnectors[listLastConnectors.length() - 1] -> getPositionItem()["X"];
        qreal y2 = listLastConnectors[listLastConnectors.length() - 1] -> getPositionItem()["Y"];
        listLastConnectors[listLastConnectors.length() - 2] -> setMyNeighbour(listLastConnectors[listLastConnectors.length() - 1]);
        listLastConnectors.clear();
        this -> addLine(x1, y1, x2, y2);
        counterClick = 0;
        modeName = "";
    }
    if (counterClick == 2 && modeName.contains("Zone")) {
        qreal x1 = listPoints[listPoints.length() - 2]["X"];
        qreal y1 = listPoints[listPoints.length() - 2]["Y"];
        qreal x2 = listPoints[listPoints.length() - 1]["X"];
        qreal y2 = listPoints[listPoints.length() - 1]["Y"];
        this -> addZone(x1, y1, x2, y2);
        counterClick = 0;
        modeName = "";
    }
}

void Widget::slot_update_spendTime() {
    spendsSeconds++;
}

void Widget::getItem(WorkItem * workItem) {
    saveLastClickItem = workItem;
    modeName = "";
}

void Widget::getConnItem(ConnItem * connItem) {
    saveLastClickItem = connItem;
    if (saveLastClickItem -> getName().contains("Connector")) {
        listLastConnectors.append(connItem);
        modeName = "Line";
    } else {
        modeName = "";
    }
}

void Widget::addSkud() {
    WorkItem* skud = new WorkItem(nullptr, "Skud_" + QString::number(getNumberOfWorkItem("Skud_")), 30, 30, 1, false, true);
    if (modeName.endsWith("") && listAllItems.indexOf(saveLastClickItem) != -1) {
        int lastClickItemIndex = listAllItems.indexOf(saveLastClickItem);
        WorkItem * temp = listAllItems[lastClickItemIndex];
        this -> redraw();
        skud -> setPos(temp -> x(), temp -> y());
        listAllItems[lastClickItemIndex] = skud;
        this -> setConnectors(skud, this -> mapConnector);
        scene -> addItem(skud);
    }
}

void Widget::addCrm() {
    WorkItem* crm = new WorkItem(nullptr, "Crm_" + QString::number(getNumberOfWorkItem("Crm_")), 30, 30, 6, false, false);
    if (modeName.endsWith("") && listAllItems.indexOf(saveLastClickItem) != -1) {
        int lastClickItemIndex = listAllItems.indexOf(saveLastClickItem);
        WorkItem * temp = listAllItems[lastClickItemIndex];
        this -> redraw();
        crm -> setPos(temp -> x(), temp -> y());
        listAllItems[lastClickItemIndex] = crm;
        this -> setConnectors(crm, this -> mapConnector);
        scene -> addItem(crm);
    }
}

void Widget::addDb() {
    WorkItem* db = new WorkItem(nullptr, "Db_" + QString::number(getNumberOfWorkItem("Db_")), 30, 30, 7, false, false);
    if (modeName.endsWith("") && listAllItems.indexOf(saveLastClickItem) != -1) {
        int lastClickItemIndex = listAllItems.indexOf(saveLastClickItem);
        WorkItem * temp = listAllItems[lastClickItemIndex];
        this -> redraw();
        db -> setPos(temp -> x(), temp -> y());
        listAllItems[lastClickItemIndex] = db;
        this -> setConnectors(db, this -> mapConnector);
        scene -> addItem(db);
    }
}

int Widget::getNumberItemFromList(WorkItem * item) {
    for (int keyItem = 0; keyItem < listAllItems.length(); keyItem++) {
        if (listAllItems[keyItem] == item) {
            return keyItem;
        }
    }
    return -1;
}

int Widget::getNumberOfWorkItem(QString searchElement) {
    int number = 0;
    if (listAllItems.length() != 0) {
        for (int i = 0; i < listAllItems.length(); i++) {
            if (listAllItems[i] -> getName().contains(searchElement)) {
                number++;
            }
        }
    }
    return number;
}

void Widget::setConnectors(WorkItem * item, QMap < QString, bool > mapConnector) {
    item -> setBuffer(new Buffer());
    ConnItem * connectorItem;
    connect(item, & WorkItem::sentMessage, item -> getBuffer(), & Buffer::getAccessToSendMessage);
    if (mapConnector["Up"]) {
        connectorItem = new ConnItem(nullptr, "Connector_" + item -> getName() + "Up",
            10, 10,
            4, false);
        connect(item -> getBuffer(), & Buffer::sentMessageToConnItem, connectorItem, & ConnItem::getMessageForSent);
        connect(connectorItem, & ConnItem::sentConnItem, this, & Widget::getConnItem);
        connectorItem -> setMyOwnerWorkItem(item);
        connectorItem -> setPos(item -> x(), item -> y() - item -> getHeight() / 2 - 10);
        connectorItem -> setZValue(std::numeric_limits < qreal > ::max());
        listAllItems.append(connectorItem);
        scene -> addItem(connectorItem);
    }

    if (mapConnector["Down"]) {
        connectorItem = new ConnItem(nullptr, "Connector_" + item -> getName() + "Down",
            10, 10,
            4, false);
        connect(item -> getBuffer(), & Buffer::sentMessageToConnItem, connectorItem, & ConnItem::getMessageForSent);
        connect(connectorItem, & ConnItem::sentConnItem, this, & Widget::getConnItem);
        connectorItem -> setMyOwnerWorkItem(item);
        connectorItem -> setPos(item -> x(), item -> y() + item -> getHeight() / 2 + 10);
        connectorItem -> setZValue(std::numeric_limits < qreal > ::max());
        listAllItems.append(connectorItem);
        scene -> addItem(connectorItem);
    }

    if (mapConnector["Left"]) {
        connectorItem = new ConnItem(nullptr, "Connector_" + item -> getName() + "Left",
            10, 10,
            4, false);
        connect(item -> getBuffer(), & Buffer::sentMessageToConnItem, connectorItem, & ConnItem::getMessageForSent);
        connect(connectorItem, & ConnItem::sentConnItem, this, & Widget::getConnItem);
        connectorItem -> setMyOwnerWorkItem(item);
        connectorItem -> setPos(item -> x() - item -> getWidth() / 2 - 10, item -> y());
        connectorItem -> setZValue(std::numeric_limits < qreal > ::max());
        listAllItems.append(connectorItem);
        scene -> addItem(connectorItem);
    }

    if (mapConnector["Right"]) {
        connectorItem = new ConnItem(nullptr, "Connector_" + item -> getName() + "Right",
            10, 10,
            4, false);
        connect(item -> getBuffer(), & Buffer::sentMessageToConnItem, connectorItem, & ConnItem::getMessageForSent);
        connect(connectorItem, & ConnItem::sentConnItem, this, & Widget::getConnItem);
        connectorItem -> setMyOwnerWorkItem(item);;
        connectorItem -> setPos(item -> x() + item -> getWidth() / 2 + 10, item -> y());
        connectorItem -> setZValue(std::numeric_limits < qreal > ::max());
        listAllItems.append(connectorItem);
        scene -> addItem(connectorItem);
    }
}

void Widget::addZone(qreal x1_coord, qreal y1_coord,
    qreal x2_coord, qreal y2_coord) {
    int width = qFabs(x2_coord - x1_coord);
    int height = qFabs(y2_coord - y1_coord);
    WorkItem * zoneItem = new WorkItem(nullptr, "Zone_" + QString::number(getNumberOfWorkItem("Zone_")),
        width, height,
        2);
    zoneItem -> setPos(x1_coord + width / 2, y1_coord + height / 2);
    modeName = "";
    counterClick = 0;
    listPoints.clear();
    qInfo() << "set mode: empty";
    listAllItems.append(zoneItem);
    this -> setConnectors(zoneItem, this -> mapConnector);
    scene -> addItem(zoneItem);
    this -> redraw();
}

void Widget::addLine(qreal x1_coord, qreal y1_coord,
    qreal x2_coord, qreal y2_coord) {
    int width = qFabs(x2_coord - x1_coord);
    int height = qFabs(y2_coord - y1_coord);
    int lengthLine = qSqrt(qPow(width, 2) + qPow(height, 2));
    WorkItem * lineItem = new WorkItem(nullptr, "Line_" + QString::number(getNumberOfWorkItem("Line")),
        lengthLine, 6,
        0);
    WorkItem * petalItem = new WorkItem(nullptr, "Line_" + QString::number(getNumberOfWorkItem("Line")) + "_petalItem",
        15, 15,
        5);
    qreal degree = 0;
    if (x1_coord <= x2_coord) {
        if (y1_coord <= y2_coord) {
            degree = qRadiansToDegrees(qAsin((qreal) height / (qreal) lengthLine));
            lineItem -> setRotation(degree);
            lineItem -> setPos(x1_coord + width / 2, y1_coord + height / 2);
            lineItem -> setZValue(std::numeric_limits < qreal > ::min());

            petalItem -> setRotation(degree * 2);
            petalItem ->setPos(x2_coord, y2_coord);
        } else {
            degree = qRadiansToDegrees(qAsin((qreal) height / (qreal) lengthLine));
            lineItem -> setRotation(degree * (-1));
            lineItem -> setPos(x1_coord + width / 2, y1_coord - height / 2);
            lineItem -> setZValue(std::numeric_limits < qreal > ::min());

            petalItem -> setRotation(degree * (-1) * 2);
            petalItem ->setPos(x2_coord, y2_coord);
        }
    } else {
        if (y1_coord <= y2_coord) {
            degree = qRadiansToDegrees(qAsin((qreal) height / (qreal) lengthLine));
            lineItem -> setRotation(degree * (-1));
            lineItem -> setPos(x1_coord - width / 2, y1_coord + height / 2);
            lineItem -> setZValue(std::numeric_limits < qreal > ::min());

            petalItem -> setRotation(degree * (-1) * 2);
            petalItem ->setPos(x2_coord, y2_coord);
        } else {
            degree = qRadiansToDegrees(qAsin((qreal) height / (qreal) lengthLine));
            lineItem -> setRotation(degree);
            lineItem -> setPos(x1_coord - width / 2, y1_coord - height / 2);
            lineItem -> setZValue(std::numeric_limits < qreal > ::min());

            petalItem -> setRotation(degree * 2);
            petalItem ->setPos(x2_coord, y2_coord);
        }
    }
    modeName = "";
    counterClick = 0;
    listPoints.clear();
    qInfo() << "set mode: empty";
    listAllItems.append(lineItem);
    scene -> addItem(lineItem);
    scene -> addItem(petalItem);
    this -> redraw();
}

QString Widget::getTime() {
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

void Widget::redraw() {
    scene -> update();
}
