#ifndef MYGAUGE_H
#define MYGAUGE_H

#include <QWidget>

class myGauge : public QWidget
{
    Q_OBJECT
public:
    explicit myGauge(QWidget *parent = nullptr);

private:
    int m_value;
    QPoint m_StartPos;
    bool m_mouseDown;

protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

signals:

public slots:

    void setValue(int v){
        if((m_value >= 0) && (m_value <= 270)){
            if(m_value != v){
                m_value = v;
                this->update();
            }
        }
    }
};

#endif // MYGAUGE_H
