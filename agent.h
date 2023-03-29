#ifndef AGENT_H
#define AGENT_H

#include <QObject>

class Agent : public QObject
{
    Q_OBJECT
public:
    Agent();
    ~Agent();
    int         levelAccess;
    QString     name;
};

#endif // AGENT_H
