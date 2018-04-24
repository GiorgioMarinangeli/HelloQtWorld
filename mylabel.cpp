#include <QMouseEvent>
#include <QPainter>

#include "mylabel.h"

myLabel::myLabel(QWidget *parent) :
    QLabel(parent)
{
    m_reverse = false;
}

void myLabel::mousePressEvent(QMouseEvent* ev){
    emit onClickEvent();
    m_reverse = !m_reverse;
    this->repaint();
}

void myLabel::paintEvent(QPaintEvent *p){

    QColor black = QColor(0,0,0,255);       // Blaxk;
    QColor white = QColor(255,255,255,255); // white

    QRect r = QRect(this->rect().x()+6, this->rect().y()+6, this->rect().width()-12, this->rect().height()-12);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QFont f;
    f.setPixelSize(20);
    painter.setFont(f);

    QFontMetrics fm(f);
    int w = fm.width(this->text());

    QPoint c = r.center();
    c.setX(c.x()-w/2);
    c.setY(c.y()+6);

    if(m_reverse){

        QPainterPath path;
        path.addRect(QRectF(0, 0, this->width(), this->height()));

        QPen pen(Qt::black, 4);
        painter.setPen(pen);
        painter.fillPath(path, Qt::darkGray);
        painter.drawPath(path);

        pen.setColor(white); //note this
        painter.setPen(pen);
    }

    painter.drawText(c,this->text());

}
