#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QObject>

class myLabel : public QLabel
{
    Q_OBJECT

private:
    bool m_reverse;

public:
    myLabel(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent* ev);
    void paintEvent(QPaintEvent *p);

signals:
    int onClickEvent();


};

#endif // MYLABEL_H
