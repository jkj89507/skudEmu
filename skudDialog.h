#ifndef SKUDDIALOG_H
#define SKUDDIALOG_H

#include <QDialog>
#include "./items/workItem.h"
#include "./items/connItem.h"
#include "myscene.h"
#include "utils.h"

namespace Ui {
class SkudDialog;
}

class SkudDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SkudDialog(QWidget *parent = nullptr);
    ~SkudDialog();

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
    Ui::SkudDialog      *ui;
    MyScene             *scene;
    int                 dialogWidth = 400;
    int                 dialogHeight = 300;
    WorkItem            *workItem;
    ConnItem            *up;
    ConnItem            *right;
    ConnItem            *down;
    ConnItem            *left;
    QMap<QString, bool> mapConnector;

    void redraw();
};

#endif // SKUDDIALOG_H
