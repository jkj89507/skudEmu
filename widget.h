#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QTimer>
#include <QPointF>
#include <QPainter>
#include <qmath.h>
#include "myscene.h"
#include "workItem.h"
#include "connItem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();


public slots:
    void slot_readClick();
    void getItem(WorkItem* workItem);
    void getConnItem(ConnItem* connItem);

private slots:
    void on_addSkud_clicked();
//    void on_addSkud_2_clicked();
    void on_addLine_clicked();
    void slot_encreseCounter();
    void slot_update_spendTime();

private:
    Ui::Widget              *ui;
    MyScene                 *scene;
    int sceneSize           = 650;
    int amountOfItemsInRow  = 0;
    QTimer                  *timer;
    QMap<int, WorkItem*>    mapAccessByNumber;
    QList<WorkItem *>       listAllItems;
    QList<QMap<QString, qreal>> listPoints;
    QString                 modeName;
    quint64                 spendsSeconds;
    QString                 spendTime;
    int                     counterClick;
    WorkItem*               saveLastClickItem;
    ConnItem*               saveLastClickConnItem;
    QList<ConnItem *>       listLastConnectors;

    void paintLine(qreal x1_coord, qreal y1_coord,
                   qreal x2_coord, qreal y2_coord);
    QString getTime();
    void setActiveItem(WorkItem* item);
    int getNumberItemFromList(WorkItem* item);
    void setConnectorsPoint(WorkItem* item);
    void drawWorkplace();
    void redraw();
};
#endif // WIDGET_H
