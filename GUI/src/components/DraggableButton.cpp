#include "components/DraggableButton.h"


DraggableButton::DraggableButton(QWidget *parent) : QPushButton("test button",parent) {}

void DraggableButton::mouseMoveEvent(QMouseEvent *event) {
    // Custom handling of mouse move event
    // Example: Print mouse position
    if(event->buttons() & Qt::LeftButton)
    {
        this->move(mapToParent(event->pos() - offset));
    }
    // If you need to move the button based on mouse movement, you can adjust its position here
    // For example:
    // this->move(mapToParent(event->pos()));
}

void DraggableButton::mousePressEvent(QMouseEvent *event)
{
    offset = event->pos();
}