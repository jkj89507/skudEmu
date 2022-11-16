#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>
#include "workItem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_addSkud_clicked();
    void on_addSkud_2_clicked();
    void on_addLine_clicked();

private:
    Ui::Widget         *ui;
    QGraphicsScene  *scene;
    QTimer          *timer;
    QList<WorkItem *> listAllItems;
};
#endif // WIDGET_H
