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

private slots:
    void on_pressMePushButton_clicked();

private:
    Ui::mainWidget *ui;
};

#endif // WIDGET_H
