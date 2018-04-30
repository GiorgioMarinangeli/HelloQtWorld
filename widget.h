#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class mainWidget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:
    bool eventFilter(QObject *target, QEvent *event);
    void timerEvent(QTimerEvent *event);

private slots:
    void slotPerTastiConIdx();
    void clickOnMyLabelSlot();

    void timerSlot();

    void on_pressMePushButton_clicked();

    void on_setLeftPushButton_clicked();

    void on_setRightPushButton_clicked();

    void on_createPushButton_clicked();

    void on_deletePushButton_clicked();

    void on_connectSignalPushButton_clicked();

    void on_disconnectSignalPushButton_clicked();

    void on_conectPage5PushButton_clicked();

    void on_quitPushButton_clicked();

    void on_startTimerCheckBox_clicked(bool checked);

private:
    Ui::mainWidget *ui;

    void findAllChildren(QWidget* pwidget);
    int m_itrator;    

    int  m_timerId;
    void clearTimerStart(int &timerId);

    QWidget* m_Container;

    int m_nStartUp;
    void ReadSettings();
    void WriteSettings();

    int ccTimer;
    QTimer* pMyTimer;
};

#endif // WIDGET_H
