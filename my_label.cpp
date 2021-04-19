#include "my_label.h"

my_label::my_label(QWidget *parent) : QLabel(parent)
{
    this->setMouseTracking(true);
}

void my_label::mouseReleaseEvent(QMouseEvent *event)
{
    this->x=event->x();
    this->y=event->y();
     emit Mouse_Release();
}

