#ifndef CONNECTORDIALOG_H
#define CONNECTORDIALOG_H

#include <QDialog>
#include "./items/workItem.h"
#include "./items/connItem.h"
#include "myscene.h"
#include "utils.h"

namespace Ui {
class ConnectorDialog;
}

class ConnectorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectorDialog(QWidget *parent = nullptr);
    ~ConnectorDialog();

signals:
    void updateStatusMapConnector();
    void sentMapConnector(QMap<QString, bool> mapConnector);

private slots:
    void onCheckBoxUpStateChanged(int state);
    void onCheckBoxRightStateChanged(int state);
    void onCheckBoxDownStateChanged(int state);
    void onCheckBoxLeftStateChanged(int state);
    void updateEnablingPushButton();
    void pushButton();

private:
    Ui::ConnectorDialog      *ui;
    MyScene                     *scene;
    int                         dialogWidth = 400;
    int                         dialogHeight = 300;
    WorkItem                    *workItem;
    ConnItem                    *up;
    ConnItem                    *right;
    ConnItem                    *down;
    ConnItem                    *left;
    QMap<QString, bool>         mapConnector;

    void redraw();
};

#endif // CONNECTORDIALOG_H
