#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QTimer>
#include <QPointF>
#include <QPainter>
#include "myscene.h"
#include "workItem.h"

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

private slots:
    void on_addSkud_clicked();
    void on_addSkud_2_clicked();
    void on_addLine_clicked();
    void slot_encreseCounter();

private:
    Ui::Widget              *ui;
    MyScene                 *scene;
    QTimer                  *timer;
    QList<WorkItem *>       listAllItems;
    QList<QMap<QString, qreal>> listPoints;
    QString                 modeName;
    int                     counterClick;
};
#endif // WIDGET_H
