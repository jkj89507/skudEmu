#include "myscene.h"

MyScene::MyScene(QObject *parent)
{
    lastClickResultsList.clear();
}

QList<QMap<QString, qreal>> MyScene::getLastClickResultsList()
{
    return lastClickResultsList;
}

void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QMap<QString, qreal> resultMap;
    qreal y_coord = event->scenePos().y();
    qreal x_coord = event->scenePos().x();
    QGraphicsScene::mousePressEvent(event);
    resultMap["Y"] = y_coord;
    resultMap["X"] = x_coord;
    lastClickResultsList.append(resultMap);
    emit signal_clickRelesed();
}

void MyScene::clearClickResultsList()
{
    lastClickResultsList.clear();
}

