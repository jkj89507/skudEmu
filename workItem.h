#ifndef WORKITEM_H
#define WORKITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>

class WorkItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    WorkItem(QObject *parent = nullptr, QString idWorkItem = "Dafault",
             int width = 30, int height = 30,
             int color = 1);
    ~WorkItem();

signals:
    void signalWtfItem(QGraphicsItem* item);

public slots:
    void syncUpdateWithTimer();

private:
    QString idWorkItem;
    int width; //Параметр длины
    int height; //Пармаетр ширины
    int color; //Пармаетр цвета
    QRectF boundingRect() const; //Отрисовка границ
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); //Отрисовка элемента
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event); //Событие перетаскивание мышкой элемента
    void mousePressEvent(QGraphicsSceneMouseEvent *event); //Событие нажатие мышкой на элемент
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event); //Событие отпускания мышки от объекта
};

#endif // WORKITEM_H
