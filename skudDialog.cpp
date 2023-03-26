#include "skudDialog.h"
#include "ui_skudDialog.h"

SkudDialog::SkudDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SkudDialog)
{
    ui->setupUi(this);
    scene = new MyScene(this);
    scene->clear();
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setRenderHint(QPainter::SmoothPixmapTransform);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по вертикали
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    mapConnector["Up"] = false;
    mapConnector["Right"] = false;
    mapConnector["Down"] = false;
    mapConnector["Left"] = false;

    Utils::drawWorkplace(scene, dialogWidth, dialogHeight);
    workItem = new WorkItem(nullptr, "Temp", 60, 60, 1);
    workItem->setPos(130, 130);
    scene->addItem(workItem);
    this->redraw();

    ui->pushButton->setEnabled(false);
    connect(ui->checkBoxUp, &QCheckBox::stateChanged, this, &SkudDialog::onCheckBoxUpStateChanged);
    connect(ui->checkBoxRight, &QCheckBox::stateChanged, this, &SkudDialog::onCheckBoxRightStateChanged);
    connect(ui->checkBoxDown, &QCheckBox::stateChanged, this, &SkudDialog::onCheckBoxDownStateChanged);
    connect(ui->checkBoxLeft, &QCheckBox::stateChanged, this, &SkudDialog::onCheckBoxLeftStateChanged);
    connect(ui->pushButton, &QPushButton::clicked, this, &SkudDialog::pushButton);
    connect(this, &SkudDialog::updateStatusMapConnector, this, &SkudDialog::updateEnablingPushButton);
}

void SkudDialog::onCheckBoxUpStateChanged(int state)
{
    if (state == Qt::Checked) {
        up = new ConnItem(nullptr, "Connector_1",
                        20, 20,
                        4, false);
        up->setPos(workItem->x(), workItem->y() - 60);
        scene->addItem(up);
        mapConnector["Up"] = true;
        emit updateStatusMapConnector();
        this->redraw();
    } else {
        scene->removeItem(up);
        up = NULL;
        mapConnector["Up"] = false;
        emit updateStatusMapConnector();
        this->redraw();
    }
}

void SkudDialog::onCheckBoxRightStateChanged(int state)
{
    if (state == Qt::Checked) {
        right = new ConnItem(nullptr, "Connector_2",
                        20, 20,
                        4, false);
        right->setPos(workItem->x() + 60, workItem->y());
        scene->addItem(right);
        mapConnector["Right"] = true;
        emit updateStatusMapConnector();
        this->redraw();
    } else {
        scene->removeItem(right);
        right = NULL;
        mapConnector["Right"] = false;
        emit updateStatusMapConnector();
        this->redraw();
    }
}

void SkudDialog::onCheckBoxDownStateChanged(int state)
{
    if (state == Qt::Checked) {
        down = new ConnItem(nullptr, "Connector_3",
                        20, 20,
                        4, false);
        down->setPos(workItem->x(), workItem->y() + 60);
        scene->addItem(down);
        mapConnector["Down"] = true;
        emit updateStatusMapConnector();
        this->redraw();
    } else {
        scene->removeItem(down);
        down = NULL;
        mapConnector["Down"] = false;
        emit updateStatusMapConnector();
        this->redraw();
    }
}
void SkudDialog::onCheckBoxLeftStateChanged(int state)
{
    if (state == Qt::Checked) {
        left = new ConnItem(nullptr, "Connector_4",
                        20, 20,
                        4, false);
        left->setPos(workItem->x() - 60, workItem->y());
        scene->addItem(left);
        mapConnector["Left"] = true;
        emit updateStatusMapConnector();
        this->redraw();
    } else {
        scene->removeItem(left);
        left = NULL;
        mapConnector["Left"] = false;
        emit updateStatusMapConnector();
        this->redraw();
    }
}

void SkudDialog::updateEnablingPushButton()
{
    if (mapConnector["Up"] || mapConnector["Right"] || mapConnector["Down"] || mapConnector["Left"]) {
        ui->pushButton->setEnabled(true);
    } else {
        ui->pushButton->setEnabled(false);
    }
}

void SkudDialog::pushButton()
{
    this->accept();
    emit sentMapConnector(mapConnector);
}

SkudDialog::~SkudDialog()
{
    delete ui;
}

void SkudDialog::redraw()
{
    scene->update();
}
