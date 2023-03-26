#ifndef CONNITEM_H
#define CONNITEM_H

#include "workItem.h"

class ConnItem : public WorkItem
{
    Q_OBJECT
public:
    ConnItem(QObject *parent = nullptr, QString idWorkItem = "Dafault",
             int width = 30, int height = 30,
             int color = 4, bool isRemovable = true);
    ~ConnItem();
    WorkItem* getOwner();
    void setMyOwnerWorkItem(WorkItem* owner);
    void setMyNeighbour(ConnItem* neighbour);
    ConnItem* getMyNeighbour();
    QMap<QString, qreal> getPositionItem();

public slots:

//    void getMyNeighbour(ConnItem* neighbour);
//    void getMessageFromWorkItem(QString message);
//    void getMessageFromAnotherConnItem(QString message);
    void getMessageForSent(QString message);

signals:
//    void sentMessageToWorkItem(QString message);
//    void sentMessageToAnotherConnItem(QString message);
    void sentConnItem(ConnItem* connItem);
//    void sentMessage(QString message);

private:
    WorkItem*       myOwner;
    ConnItem*       myNeighbour;
    QMap<QString, qreal> positionItem;
    QString         message;
    void            mousePressEvent(QGraphicsSceneMouseEvent *event);
    void            setMessage(QString message);
};

#endif // ACTIVEITEM_H