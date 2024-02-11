#include "iostream"

#include "components/DraggableButton.h"


DraggableButton::DraggableButton(QWidget *parent) : QPushButton("test button",parent) {
    setIcon(QIcon(":/images/GS-valve-open.svg"));

}

void DraggableButton::mouseMoveEvent(QMouseEvent *event) {
    // Custom handling of mouse move event
    // Example: Print mouse position
    int yOffset = 296;
    int xOffset = 25;
    float imWidth = 1209;
    float imHeight = 749;
    std::cout << "pos: ";
    std::cout << (mapToParent(event->pos() - offset).x()-xOffset) / imWidth << ", ";
    std::cout << (mapToParent(event->pos() - offset).y()-yOffset) / imHeight << std::endl;
    
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