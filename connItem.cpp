#include "connItem.h"

ConnItem::ConnItem(QObject *parent, QString idWorkItem, int width, int height, int color, bool isRemovable)
    : WorkItem(parent, idWorkItem,
               width, height,
               color, isRemovable)
{
}

ConnItem::~ConnItem()
{
}

QMap<QString, qreal> ConnItem::getPositionItem()
{
    return positionItem;
}

void ConnItem::setMyOwnerWorkItem(WorkItem* owner) {
    myOwner = owner;
}

void ConnItem::setMyNeighbour(ConnItem* neighbour) {
    myNeighbour = neighbour;
}

ConnItem* ConnItem::getMyNeighbour() {
    return myNeighbour;
}

WorkItem* ConnItem::getOwner() {
    return myOwner;
}

void ConnItem::getMessageForSent(QString message)
{
    if (myNeighbour != nullptr) {
        myNeighbour->myOwner->getMessage(message);
    }

}


void ConnItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    /* При нажатии мышью на графический элемент
     * заменяем курсор на руку, которая держит этот элемента
     * */
    positionItem["Y"] = this->y();
    positionItem["X"] = this->x();
    qInfo() << "mousePressEvent Y: " << this->y() << " X: " << this->x();
    emit sentConnItem(this);
//    if (isRemovable) {
//        this->setCursor(QCursor(Qt::ClosedHandCursor));
//        Q_UNUSED(event);
//    }

}


