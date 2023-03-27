#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QTimer>
#include <QPointF>
#include <QPainter>
#include <qmath.h>
#include "myscene.h"
#include "items/workItem.h"
#include "items/connItem.h"
#include "buffer.h"
#include "connectorDialog.h"
#include "utils.h"

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
    void on_addZone_clicked();
    void on_addLine_clicked();
    void slot_encreseCounter();
    void slot_update_spendTime();
    void getMapConnector(QMap<QString, bool> mapConnector);
//    void openSkudDialog();

private:
    Ui::Widget              *ui;
    MyScene                 *scene;
    ConnectorDialog         *connDialog;
    int sceneSizeWidth      = 1450;
    int sceneSizeHeight     = 970;
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
    QMap<QString, bool>     mapConnector;

    void addSkud();
    void addZone(qreal x1_coord, qreal y1_coord,
                 qreal x2_coord, qreal y2_coord);
    void addLine(qreal x1_coord, qreal y1_coord,
                   qreal x2_coord, qreal y2_coord);
    void updateMapConnector();
    QString getTime();
    int getNumberItemFromList(WorkItem* item);
    int getNumberOfWorkItem(QString searchElement);
    void setConnectors(WorkItem* item, QMap<QString, bool> mapConnector);
    void redraw();
};
#endif // WIDGET_H
