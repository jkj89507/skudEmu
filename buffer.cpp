#include "buffer.h"

Buffer::Buffer(QObject *parent)
    : QObject{parent}
{
}

Buffer::~Buffer()
{
}

void Buffer::setMessage(QString bufferMessage)
{
}

void Buffer::getAccessToSendMessage(QString message) {
    qInfo() << "Buffer get message: " << message;
    emit sentMessageToConnItem(message);
}
