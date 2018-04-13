#include <QMessageBox>
#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainWidget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pressMePushButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText(" Hello Qt World !!");
    msgBox.exec();
}
