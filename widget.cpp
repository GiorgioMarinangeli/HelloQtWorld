#include <QMessageBox>
#include <QDebug>
#include <QDial>
#include "widget.h"
#include "ui_widget.h"

//https://wiki.qt.io/Qt_for_Beginners

//----------------------------------------------------------------------------------------
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    m_Container(NULL),
    ui(new Ui::mainWidget)
{
    ui->setupUi(this);

    qDebug() << "Find all children";
    m_itrator= 0;
    findAllChildren(this);

    qDebug() << "Install Event Filter";
    ui->padWidget->installEventFilter(this);
    ui->muroWidget->installEventFilter(this);

    qDebug() << "Connect Cliccable";
    connect(ui->labelCliccabile,SIGNAL(onClickEvent()),this,SLOT(clickOnMyLabelSlot()));

    ReadSettings();
    WriteSettings();
}
//----------------------------------------------------------------------------------------
Widget::~Widget()
{
    delete ui;
}

//--------------------------------------------------------------------------------------------------
void Widget::ReadSettings(){

    //QString str = "/usr/local/etc/radiolab.conf";
    //QSettings settings(str,QSettings::IniFormat);

    QSettings settings;

    QVariant v = settings.value("N_START_UP");
    if( v.isValid() ){
        m_nStartUp = v.toInt();
        m_nStartUp++;
        ui->settingsLabel->setText(QString("Ciao, questa è la %1° volta che avvi questa demo !!").arg(m_nStartUp));
    }else{
        ui->settingsLabel->setText(" ");
    }
}

//--------------------------------------------------------------------------------------------------
void Widget::WriteSettings(){

    //QString str = gStartDir.left(gStartDir.lastIndexOf(QDir::separator())) + QDir::separator() + "config.ini";
    //QString str = "/usr/local/etc/radiolab.conf";
    //QSettings settings(str,QSettings::IniFormat);

    QSettings settings;

    settings.clear();

    settings.setValue("N_START_UP",  m_nStartUp);
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

//----------------------------------------------------------------------------------------
void Widget::slotPerTastiConIdx(){

    QPushButton* p = (QPushButton*)sender();
    QVariant v = p->property("idx");
    if(v.isValid()){
        QMessageBox msgBox;
        msgBox.setText(QString("Premuto il tasto %1").arg(v.toInt()));
        msgBox.exec();
    }
}
//----------------------------------------------------------------------------------------
void Widget::on_conectPage5PushButton_clicked()
{
    foreach(QObject *child,ui->page_5->children()) {

        if(child->isWidgetType()){

            QPushButton*p = (QPushButton*)child;

            QVariant v = p->property("idx");

            if ( v.isValid() ){
                connect(p, SIGNAL(clicked()),this,SLOT(slotPerTastiConIdx()));
            }
        }
    }
}

//----------------------------------------------------------------------------------------
void Widget::timerEvent(QTimerEvent *event){
    if(event->timerId() == m_timerId){
        this->killTimer(m_timerId);
        m_timerId = -1;
        ui->msglabel->setText("");
    }
}
//----------------------------------------------------------------------------------------
void Widget::clearTimerStart(int &timerId){
    if(timerId != -1){
        this->killTimer(timerId);
    }

    timerId = this->startTimer(1000);
}

//----------------------------------------------------------------------------------------
bool Widget::eventFilter(QObject *target, QEvent *event)
{
    if (target == ui->muroWidget ){

        if ( event->type() == QEvent::KeyPress ) {
            ui->msglabel->setText("Premuto Mouse su Muro");
            clearTimerStart(m_timerId);
            return(true);
        }else
        if ( event->type() == QEvent::MouseButtonRelease ) {
            ui->msglabel->setText("Hai rilasciato il Mouse su Muro");
            clearTimerStart(m_timerId);
            return(true);
        }

    }else

    if (target == ui->padWidget ){

        if ( event->type() == QEvent::MouseButtonPress ) {
            ui->msglabel->setText("Premuto Mouse su Pad");
            clearTimerStart(m_timerId);
            return(true);
        }else
        if ( event->type() == QEvent::MouseMove ) {
            ui->msglabel->setText("Stai muovendo il mouse sopra Pad");
            clearTimerStart(m_timerId);
            return(true);
        }
    }

    return QWidget::eventFilter(target, event);
}

//----------------------------------------------------------------------------------------
void Widget::clickOnMyLabelSlot(){

    QMessageBox msgBox;
    msgBox.setText(QString("Hai cliccato sulla mia Label !!"));
    msgBox.exec();
}
//----------------------------------------------------------------------------------------
void Widget::on_quitPushButton_clicked()
{
    this->close();
}
