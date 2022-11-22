#ifndef MYSCENE_H
#define MYSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

class MyScene: public QGraphicsScene
{
    Q_OBJECT

public:
    explicit MyScene(QObject *parent = nullptr);
    QList<QMap<QString, qreal>> getLastClickResultsList();
    void clearClickResultsList();

private:
    QList<QMap<QString, qreal>> lastClickResultsList;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void signal_clickRelesed();

};
#endif // MYSCENE_H
