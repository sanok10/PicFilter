#ifndef LABEL_H
#define LABEL_H


#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include<QEvent>
#include <QWheelEvent>
#include <QKeyEvent>
class my_label:public QLabel
{
    Q_OBJECT
public:
     int x,y;
    explicit my_label(QWidget *parent = nullptr);
    void mouseReleaseEvent(QMouseEvent *event);
signals:
    void Mouse_Release();
};

#endif // MY_LABEL_H
