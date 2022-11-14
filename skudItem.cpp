#include "skudItem.h"

SkudItem::SkudItem(QObject *parent)
    : QObject{parent}, QGraphicsItem()
{

}

SkudItem::~SkudItem()
{
}

void SkudItem::checkTimer()
{
//    QList<QGraphicsItem *> itemsInActiveArea = scene
}

QRectF SkudItem::boundingRect() const
{
    return QRectF (-30,-30,60,60);
}

void SkudItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::green);
    painter->drawRect(-30,-30,60,60);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void SkudItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPos(mapToScene(event->pos()));
}

void SkudItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    /* При нажатии мышью на графический элемент
     * заменяем курсор на руку, которая держит этот элемента
     * */
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void SkudItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    /* При отпускании мышью элемента
     * заменяем на обычный курсор стрелку
     * */
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}
