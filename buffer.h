#ifndef BUFFER_H
#define BUFFER_H

#include <QObject>
#include "workItem.h"
#include "connItem.h"

class Buffer: public QObject
{
    Q_OBJECT
public:
    Buffer(QObject *parent = nullptr);
    ~Buffer();
    void setMessage(QString bufferMessage);

//    void setLeftConnItem(ConnItem* connItem);
//    void setRightConnItem(ConnItem* connItem);
//    void setUpConnItem(ConnItem* connItem);
//    void setDownConnItem(ConnItem* connItem);

    void setWorkItem(WorkItem* workItem);

signals:
    void sentMessageToConnItem(QString message);

public slots:
    void getAccessToSendMessage(QString message);


private:
    WorkItem*       parentWorkItem;
    ConnItem*       upConnItem;
    ConnItem*       downConnItem;
    ConnItem*       leftConnItem;
    ConnItem*       rightConnItem;

};
#endif // BUFFER_H
