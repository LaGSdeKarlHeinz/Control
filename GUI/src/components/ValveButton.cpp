#include <iostream>
#include<unistd.h> 

#include <QIcon>
#include <QLabel>
#include <QMouseEvent>
#include <QTimer>
#include <QtSvg/QSvgRenderer>
#include <QPainter>
#include <QTransform>

#include "components/ValveButton.h"

ValveButton::ValveButton(Orientation orientation, QWidget *parent) : QLabel(parent), currentState(Unknown), iconSize(52, 52) {
    // Set initial state and update button icon
    // Change this to set the initial state as needed
    this->orientation = orientation;
    setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    setObjectName("valveButton");
    resetStyle();
    setState(Open);
    
    
}

void ValveButton::setState(State state) {
    if (currentState != state) {
        currentState = state;
        updateButtonIcon();
    }
}

void ValveButton::updateButtonIcon() {
    QString iconFilePath;
    switch (currentState) {
        case Open:
            iconFilePath = ":/images/GS-valve-open.svg";
            break;
        case Close:
            iconFilePath = ":/images/GS-valve-close.svg";
            break;
        case Unknown:
            iconFilePath = ":/images/GS-valve-unknown.svg";
            break;
    
    }

    QIcon icon(iconFilePath);
    QTransform transform;
    QPixmap newPixmap;
    switch (currentState)
    {
        case Open:
            if (orientation == Horizontal) {
                newPixmap = icon.pixmap(iconSize).transformed(transform.rotate(90));
                break;
            }
            newPixmap = icon.pixmap(iconSize).transformed(transform.rotate(0));
            break;
        case Close: 
            if (orientation == Horizontal) {
                newPixmap = icon.pixmap(iconSize).transformed(transform.rotate(0));
                break;
            }
            newPixmap = icon.pixmap(iconSize).transformed(transform.rotate(90));
            break;
        case Unknown: 
            newPixmap = icon.pixmap(iconSize).transformed(transform.rotate(180));
            break;
    } 
    setPixmap(newPixmap);
   
    
    update();
}

ValveButton::State ValveButton::getState() {
    return currentState;
}

void ValveButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        emit clicked();
      
        setStyleSheet(QString(R"(
            #valveButton {
                background:transparent;
                border-radius: 10%;
            }
            #valveButton:hover {
                background: rgba(90, 90, 90, 130);
            }
            
        )"));
        
        QTimer::singleShot(100,  [this]() {
            this->resetStyle();
        });
        
        
       
}

void ValveButton::resetStyle() {
    setStyleSheet(QString(R"(
            #valveButton {
                background:transparent;
                border-radius: 10%;
            }
            #valveButton:hover {
                background: rgba(90, 90, 90, 90);
            }
            
        )"));
}