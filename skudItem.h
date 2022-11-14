#ifndef SKUDITEM_H
#define SKUDITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>

class SkudItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit SkudItem(QObject *parent = nullptr);
    ~SkudItem();

signals:

public slots:
    void checkTimer();

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SKUDITEM_H
