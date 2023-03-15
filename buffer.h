#ifndef BUFFER_H
#define BUFFER_H

#include <QObject>
#include <QDebug>

class Buffer: public QObject
{
    Q_OBJECT
public:
    Buffer(QObject *parent = nullptr);
    ~Buffer();
    void setMessage(QString bufferMessage);

signals:
    void sentMessageToConnItem(QString message);

public slots:
    void getAccessToSendMessage(QString message);


};
#endif // BUFFER_H
