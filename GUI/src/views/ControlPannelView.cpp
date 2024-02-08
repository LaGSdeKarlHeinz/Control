/**
    @authors M.Rochat & E.Dutruy (Co-TL GS 23-24)
    @date 06-02-2024
    @brief QFrame displaying global data
*/

#include <memory>
#include <iostream>

#include <QLabel>
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QMatrix2x2>

#include "ControlPannelView.h"
#include "../Setup.h"

ControlPannelView::ControlPannelView(QWidget *parent) : QFrame(parent) {
    
    setObjectName("ControlPannel");
    setStyleSheet("background:transparent");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    toggled = false;
    // Add a QLabel to display text
    displayText = std::make_unique<QLabel>("This is DataView");
    displayText->setAlignment(Qt::AlignCenter);
    
    setupExpandButton();

    borderOffset = 9;

    controlContainerWidget = new QWidget(this);
    controlContainerWidget->setStyleSheet("background:yellow");

    QLabel *l = new QLabel("test");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(expandButton, 1, Qt::AlignHCenter); 
    layout->addWidget(controlContainerWidget, 1, Qt::AlignHCenter);
    layout->setSpacing(0);

    QVBoxLayout *containerLayout = new QVBoxLayout(controlContainerWidget);
    containerLayout->addWidget(l, 1);
    
    controlContainerWidget->setFixedHeight(240);    
    
    connect(expandButton, &QPushButton::clicked, this, &ControlPannelView::expandClicked);
    
    resizeWidget();
    
}

void ControlPannelView::resizeEvent(QResizeEvent *event) {
    resizeWidget();    
}

void ControlPannelView::setupExpandButton() {

    expandButton = new QPushButton(this);
    expandButton->setObjectName("expandButton");
    QString buttonStyle = QString(R"(
        #expandButton {
            background: %1;
            border-top-left-radius: 10%;
            border-top-right-radius: 10%;
        }
    )")
    .arg(col::complementary);
    expandButton->setStyleSheet(buttonStyle);

    // button icon : https://icones8.fr/icon/7LmItvRdpSjs/up-arrow
    buttonPixMap = QPixmap(":/icons/up-arrow.png");
   
    QIcon buttonIcon(buttonPixMap);
    
    expandButton->setFixedHeight(35);
    expandButton->setIcon(buttonIcon);
    expandButton->setIconSize(QSize(64, 64));
    
    

}


void ControlPannelView::resizeWidget() {
    int windowWidth = parentWidget()->width();
    int newWidth(windowWidth*mws::middleSectionWidth/100);
    int newHeight(controlContainerWidget->height() + expandButton->height());
    setFixedWidth(newWidth);
    
    move(QPoint((windowWidth-newWidth)/2, getHeightPos()));
    // Set a minimum height to ensure visibility
    setFixedHeight(newHeight);    

    QPoint p = QWidget::mapTo(this, QPoint(width()/2-expandButton->width()/2, 0));
    // expandButton->move(p);
    controlContainerWidget->setFixedWidth(newWidth);
    //controlContainerWidget->move(0, expandButton->height());
}

void ControlPannelView::expandClicked() {
    toggled = !toggled;
    QPropertyAnimation* anim = new QPropertyAnimation(this, "pos");
	anim->setDuration(1000);
	anim->setEasingCurve(QEasingCurve::Type::OutQuart);
	anim->setStartValue(pos());
	anim->setEndValue(QPoint(pos().x(), getHeightPos()));
	anim->start(QAbstractAnimation::DeleteWhenStopped);
    QTransform transform;
    buttonPixMap = buttonPixMap.transformed(transform.rotate(180));
    QIcon buttonIcon(buttonPixMap);    
    expandButton->setFixedHeight(35);
    expandButton->setIcon(buttonIcon);
    expandButton->setIconSize(QSize(64, 64));
    
    // resizeWidget();
}

int ControlPannelView::getHeightPos() {
    int windowWidth = parentWidget()->width();
    int newHeight(controlContainerWidget->height() + expandButton->height());
    int newY;
    if (toggled) {
        newY = parentWidget()->height()-newHeight;

    } else {
        newY = parentWidget()->height()-expandButton->height()-borderOffset;
        
    }
    
    return newY;
}