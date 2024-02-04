#include "DataView.h"
#include <QLabel>
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>

DataView::DataView(QWidget *parent) : QFrame(parent) {
    // Set up the appearance or behavior as needed

    setStyleSheet("background-color: lightblue;");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    // Add a QLabel to display text
    displayText = new QLabel("This is DataView");
    displayText->setAlignment(Qt::AlignCenter);

    QLabel *text2 = new QLabel("this is second test");
    text2->setAlignment(Qt::AlignCenter);

    QLabel *text3 = new QLabel("this is test 3");
    text3->setAlignment(Qt::AlignCenter);
    text3->setText("test reset text");
    QHBoxLayout *layout = new QHBoxLayout(this);
    QWidget *widget = new QWidget;
    
    QVBoxLayout *layout2 = new QVBoxLayout(widget);
    layout2->addWidget(text2, 3); 
    layout2->addWidget(text3, 2);
    layout->addWidget(displayText, 2); 
    layout->addWidget(widget, 2);

}

