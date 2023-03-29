#include "workItem.h"

WorkItem::WorkItem(QObject * parent, QString idWorkItem,
        int width, int height,
        int color, bool isRemovable,
        bool isClickable): QObject {
        parent
    }, QGraphicsItem(),
    idWorkItem(idWorkItem), width(width),
    height(height), color(color),
    isRemovable(isRemovable), isClickable(isClickable) {}

WorkItem::~WorkItem() {}

int WorkItem::getWidth() {
    return width;
}

int WorkItem::getHeight() {
    return height;
}

QMap < QString, qreal > WorkItem::getPositionItem() {
    return positionItem;
}

QString WorkItem::getName() {
    return idWorkItem;
}

void WorkItem::getMessage(QString message) {
    qInfo() << idWorkItem << " getMessage: " << message;
    if (idWorkItem.contains("Crm"))
    {
        emit sentMessage(message);
    }
}

void WorkItem::syncUpdateWithTimer() {
    //Получить элементы находящиееся в определенной области видимости
    //    QList<QGraphicsItem *> itemsInActiveArea = scene()->items(
    //                QPolygonF() << mapToScene((-1) * (width/2) - 15, (-1) * (height/2) + 15)
    //                << mapToScene((width/2) + 15, (-1) * (height/2) - 15)
    //                << mapToScene((width/2) + 15, (height/2) + 15)
    //                << mapToScene((-1) * (width/2) - 15, (height/2) + 15));

    //    foreach (QGraphicsItem* itemInActiveArea, itemsInActiveArea) {
    //        if (itemInActiveArea == this) {
    //            continue;
    //        }
    //        emit signalWtfItem(itemInActiveArea);
    //    }
}

void WorkItem::setBuffer(Buffer *buffer) {
    this -> buffer = buffer;
}

Buffer * WorkItem::getBuffer() {
    return this -> buffer;
}

QRectF WorkItem::boundingRect() const {
    return QRectF(QPointF((-1) * (width / 2), (-1) * (height / 2)), QSizeF(width, height));
}

void WorkItem::paint(QPainter * painter,
    const QStyleOptionGraphicsItem * option, QWidget * widget) {
    QPolygon polygon;
    polygon << QPoint((-1) * (width / 2), (-1) * (height / 2)) <<
        QPoint((width / 2), (-1) * (height / 2)) <<
        QPoint((width / 2), (height / 2)) <<
        QPoint((-1) * (width / 2), (height / 2));
    switch (color) {
        // Цвет линии
        case 0: {
            painter -> setBrush(QColor(3, 248, 252));
            painter -> drawPolygon(polygon);
            break;
        }
        case 1: {
            // СКУД картика
            painter -> drawPolygon(polygon);
            QPixmap pixmap("C:/Qt/workplace/skudEmu/images/skud.png");
            painter -> drawPixmap(-15, -15, 30, 30, pixmap);
            break;
        }
        case 2: {
            // Цвет зоны
            painter -> setBrush(QColor(242, 201, 78, 180));
            painter -> drawPolygon(polygon);
            break;
        }
        case 3: {
            // Цвет Активной точки
            painter -> setBrush(Qt::white);
            painter -> drawPolygon(polygon);
            break;
        }
        case 4: {
            // Цвет Коннектора точку
            painter -> setBrush(QColor(66, 242, 245, 180));
            painter -> drawPolygon(polygon);
            break;
        }
        case 5: {
            // Цвет Конца линии
            painter -> setBrush(Qt::yellow);
            painter -> drawPolygon(polygon);
            break;
        }
        case 6: {
            // CRM картика
            painter -> drawPolygon(polygon);
            QPixmap pixmap("C:/Qt/workplace/skudEmu/images/crm.png");
            painter -> drawPixmap(-15, -15, 30, 30, pixmap);
            break;
        }
        case 7: {
            // БД картика
            painter -> drawPolygon(polygon);
            QPixmap pixmap("C:/Qt/workplace/skudEmu/images/database.png");
            painter -> drawPixmap(-15, -15, 30, 30, pixmap);
            break;
        }

        default: {
            painter -> setBrush(Qt::black);
            painter -> drawPolygon(polygon);
            break;
        }
    }
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void WorkItem::mouseMoveEvent(QGraphicsSceneMouseEvent * event) {
    //    if (isRemovable) {
    //        this->setPos(mapToScene(event->pos()));
    //        qInfo() << "X:" << this->pos().x() << "Y:" << this->pos().y();
    //    }

}

void WorkItem::mousePressEvent(QGraphicsSceneMouseEvent * event) {
    /* При нажатии мышью на графический элемент
     * заменяем курсор на руку, которая держит этот элемента
     * */
    if (isClickable) {
        positionItem["Y"] = this -> y();
        positionItem["X"] = this -> x();
        qInfo() << "mousePressEvent Y: " << this -> y() << " X: " << this -> x();
        emit sentItem(this);
        if (!idWorkItem.contains("Active")) {
            qInfo() << this -> getName() << " sent Message";
            emit sentMessage("Hello from " + this -> getName());
            //    if (isRemovable) {
            //        this->setCursor(QCursor(Qt::ClosedHandCursor));
            //        Q_UNUSED(event);
            //    }
        }
    }
}

void WorkItem::mouseReleaseEvent(QGraphicsSceneMouseEvent * event) {
    /* При отпускании мышью элемента
     * заменяем на обычный курсор стрелку
     * */
    if (isRemovable) {
        this -> setCursor(QCursor(Qt::ArrowCursor));
        Q_UNUSED(event);
    }

}
