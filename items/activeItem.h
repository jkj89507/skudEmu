#ifndef CONNECTORITEM_H
#define CONNECTORITEM_H

#include <workItem.h>

class ConnectorItem : public WorkItem
{
    Q_OBJECT
public:
    ConnectorItem(QObject *parent = nullptr, QString idWorkItem = "Dafault",
             int width = 30, int height = 30,
             int color = 1, bool isRemovable = true);
    ~ConnectorItem();
};

#endif // CONNECTORITEM_H
