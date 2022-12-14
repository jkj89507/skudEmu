#include "workItem.h"

WorkItem::  WorkItem(QObject *parent, QString idWorkItem, int width, int height, int color)
    : QObject{parent}, QGraphicsItem(), idWorkItem(idWorkItem), width(width), height(height), color(color)
{
}

WorkItem::~WorkItem()
{
}

void WorkItem::syncUpdateWithTimer()
{
    QList<QGraphicsItem *> itemsInActiveArea = scene()->items(
                QPolygonF() << mapToScene((-1) * (width/2) - 15, (-1) * (height/2) + 15)
                << mapToScene((width/2) + 15, (-1) * (height/2) - 15)
                << mapToScene((width/2) + 15, (height/2) + 15)
                << mapToScene((-1) * (width/2) - 15, (height/2) + 15));

    foreach (QGraphicsItem* itemInActiveArea, itemsInActiveArea) {
        if (itemInActiveArea == this) {
            continue;
        }
        emit signalWtfItem(itemInActiveArea);
    }
}

QRectF WorkItem::boundingRect() const
{
    return QRectF(QPointF((-1) * (width/2), (-1) * (height/2)), QSizeF(width, height));
}

void WorkItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPolygon polygon;
    polygon << QPoint((-1) * (width/2), (-1) * (height/2))
            << QPoint((width/2), (-1) * (height/2))
            << QPoint((width/2), (height/2))
            << QPoint((-1) * (width/2), (height/2));
    switch (color) {
        case 0:
        {
            painter->setBrush(QColor(3, 248, 252));
            break;
        }
        case 1:
        {
            painter->setBrush(Qt::green);
            break;
        }
        case 2:
        {
            painter->setBrush(Qt::blue);
            break;
        }
        default:
        {
            painter->setBrush(Qt::black);
            break;
        }
    }
    painter->drawPolygon(polygon);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void WorkItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPos(mapToScene(event->pos()));
    qInfo() << "X:" << this->pos().x() << "Y:" << this->pos().y();
}

void WorkItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    /* ?????? ?????????????? ?????????? ???? ?????????????????????? ??????????????
     * ???????????????? ???????????? ???? ????????, ?????????????? ???????????? ???????? ????????????????
     * */
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void WorkItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    /* ?????? ???????????????????? ?????????? ????????????????
     * ???????????????? ???? ?????????????? ???????????? ??????????????
     * */
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}
