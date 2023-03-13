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

//void Buffer::setLeftConnItem(ConnItem* connItem)
//{
//    this->leftConnItem = connItem;
//}

//void Buffer::setRightConnItem(ConnItem* connItem)
//{
//    this->rightConnItem = connItem;
//}

//void Buffer::setUpConnItem(ConnItem* connItem)
//{
//    this->upConnItem = connItem;
//}

//void Buffer::setDownConnItem(ConnItem* connItem)
//{
//    this->downConnItem = connItem;
//}

void Buffer::setWorkItem(WorkItem* workItem)
{
    this->parentWorkItem = workItem;
}

void Buffer::getAccessToSendMessage(QString message) {
    emit sentMessageToConnItem(message);
}
