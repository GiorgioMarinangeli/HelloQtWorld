#include <QMessageBox>
#include <QDebug>
#include <QDial>
#include "widget.h"
#include "ui_widget.h"
//----------------------------------------------------------------------------------------
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    m_Container(NULL),
    ui(new Ui::mainWidget)
{
    ui->setupUi(this);

    m_itrator= 0;
    findAllChildren(this);

}
//----------------------------------------------------------------------------------------
Widget::~Widget()
{
    delete ui;
}

//----------------------------------------------------------------------------------------
void Widget::findAllChildren(QWidget* pwidget){

    QList<QObject*> list = pwidget->children();

    m_itrator++;

    foreach (QObject* obj, list) {
        if(obj->isWidgetType()){

            QString s = QString::null;

            for(int i=0;i<m_itrator;i++){
                s.append("-");
            }

            qDebug() << s << obj;

           findAllChildren((QWidget*)obj);

           m_itrator--;
        }
    }
}
//----------------------------------------------------------------------------------------
void Widget::on_pressMePushButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText(" Hello Qt World !!");
    msgBox.exec();
}
//----------------------------------------------------------------------------------------
void Widget::on_setLeftPushButton_clicked()
{
    ui->iconLabel->setParent(ui->leftWidget);
    ui->iconLabel->show();

}
//----------------------------------------------------------------------------------------
void Widget::on_setRightPushButton_clicked()
{
    ui->iconLabel->setParent(ui->rightWidget);
    ui->iconLabel->show();
}
//----------------------------------------------------------------------------------------
void Widget::on_createPushButton_clicked()
{
    m_Container = new QWidget(ui->createWidget);

    m_Container->setGeometry(0,0,ui->createWidget->width(),ui->createWidget->height());
    m_Container->setStyleSheet(QString("background-color: rgb(170, 255, 127);"));
    m_Container->show();

    QLabel*  pLabel = new QLabel(m_Container);
    pLabel->setGeometry(2,2,120,20);
    pLabel->setStyleSheet(QString("QWidget{background-color: rgb(255, 255, 255)};"));
    pLabel->setText("Porva Prova");
    pLabel->show();

    QPushButton*  pBtn = new QPushButton(m_Container);
    pBtn->setGeometry(60,50,100,20);
    pBtn->setText("Pulsante !!");
    pBtn->show();


    QDial* pDial = new QDial(m_Container);
    pDial->setGeometry(100,100, 100, 100);
    pDial->show();

    QSlider* pSlider = new QSlider(m_Container);
    pSlider->setGeometry(400,80, 40, 150);
    pSlider->show();

}
//----------------------------------------------------------------------------------------
void Widget::on_deletePushButton_clicked()
{
    if( m_Container != NULL){
        delete m_Container;
        m_Container = NULL;
    }
}
//----------------------------------------------------------------------------------------
void Widget::on_connectSignalPushButton_clicked()
{
    connect(ui->verticalSlider, SIGNAL(valueChanged(int)),ui->lcdNumber,        SLOT(display(int)));
    connect(ui->dial,           SIGNAL(valueChanged(int)),ui->lcdNumber,        SLOT(display(int)));
    connect(ui->verticalSlider, SIGNAL(valueChanged(int)),ui->dial,             SLOT(setValue(int)));
    connect(ui->dial,           SIGNAL(valueChanged(int)),ui->verticalSlider,   SLOT(setValue(int)));

}
//----------------------------------------------------------------------------------------
void Widget::on_disconnectSignalPushButton_clicked()
{
    disconnect(ui->verticalSlider, SIGNAL(valueChanged(int)),ui->lcdNumber,        SLOT(display(int)));
    disconnect(ui->dial,           SIGNAL(valueChanged(int)),ui->lcdNumber,        SLOT(display(int)));
    disconnect(ui->verticalSlider, SIGNAL(valueChanged(int)),ui->dial,             SLOT(setValue(int)));
    disconnect(ui->dial,           SIGNAL(valueChanged(int)),ui->verticalSlider,   SLOT(setValue(int)));
}
