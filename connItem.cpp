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

void ConnItem::setMyOwnerWorkItem(WorkItem* owner) {
    myOwner = owner;
}

void ConnItem::getMyNeighbour(ConnItem* neighbour) {
    myNeighbour = neighbour;
}

WorkItem* ConnItem::getOwner() {
    return myOwner;
}

