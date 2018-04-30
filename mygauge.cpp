#include <QPainter>
#include <QKeyEvent>
#include "mygauge.h"
//------------------------------------------------------------------------------
myGauge::myGauge(QWidget *parent) : QWidget(parent)
{
    m_value      = 0;
    m_mouseDown = false;
}
//------------------------------------------------------------------------------
void myGauge::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    //Trovo l'area
    int extent;
    if(width() > height()){
        extent = height()-20;
    }else{
        extent = width() -20;
    }

    //Disegno il background
    painter.translate((width()-extent) / 2, (height()-extent) / 2);
    painter.setPen(Qt::white);
    painter.setBrush(Qt::black);
    painter.drawEllipse(0,0,extent,extent);

    //Disegno le tacche
    //Lo facciamo ruotando il sistema di coordinate intorno al punto centrale dell'oggetto
    //Save restore rimette tutto apposto e annulla le trasformazioni fatte
    //E' meglio salvare/ripristinare il sistema in quanto fare una nuova rotazione per tornare da capo
    //potrebbecausare dei problemi e non essere precisa.
    //Notare che il disegno della linea è fatto sempre nello stesso modo -> giriamo le coordinate.
    painter.translate(extent/2,extent/2);
    for(int angle=0;angle<=270;angle +=45){
        painter.save();
        painter.rotate(angle + 135);
        painter.drawLine(extent*0.4,0,extent*0.48,0);
        painter.restore();
    }

    painter.save();
    painter.rotate(m_value - 45);
    QPolygon polygon;
    polygon << QPoint(-extent*0.05, extent*0.05) << QPoint(-extent*0.05, -extent*0.05) << QPoint(-extent*0.46, 0);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::red);
    painter.drawPolygon(polygon);
    painter.restore();

    if(this->hasFocus()) {
        painter.translate(-width()/2, -height()/2);
        painter.setPen(Qt::black);
        painter.setBrush(Qt::NoBrush);
        painter.drawRect(4,4,this->width()-4,this->height()-4);
    }

}

//------------------------------------------------------------------------------
void myGauge::keyPressEvent(QKeyEvent *event){

    switch(event->key()){
        case Qt::Key_1:
            if((m_value+1)<=270)
                this->setValue(m_value+1);
            break;
        case Qt::Key_2:
            if((m_value-1)>=0)
                this->setValue(m_value-1);
            break;
    }
}
//------------------------------------------------------------------------------
void myGauge::mousePressEvent(QMouseEvent *event){

    m_StartPos = event->pos();
    m_mouseDown= true;

}
//------------------------------------------------------------------------------
void myGauge::mouseReleaseEvent(QMouseEvent *event){

    m_mouseDown = false;

}
//------------------------------------------------------------------------------
void myGauge::mouseMoveEvent(QMouseEvent *event){

    if( m_mouseDown == true ){

        int c = (m_StartPos.y() - event->pos().y())/2;

        m_StartPos = event->pos();

        this->setValue(m_value + c);

    }
}


