#include <iostream>

#include <QVBoxLayout>
#include <QPixmap>
#include <QLayout>

#include "TimerView.h"
#include "MainWindow.h"
#include "../Setup.h"



TimerView::TimerView(QString title, QWidget *parent) : QWidget(parent), timer1Count(0), timerTitle(title) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    setObjectName("TimerView");
    
    

    timer1Label.setText(formatTime(timer1Count));
    timer1Label.setObjectName("child");
    // clock icon from https://icons8.com/icon/113106/clock
    QPixmap pm(":/icons/clock-icon-white.png");
    originalPixmap = pm;
    imageLabel = new QLabel;
    
    
    // imageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    imageLabel->setObjectName("child");
    
    imageLabel->setPixmap(pm.scaled(this->widthMM(), this->heightMM(), Qt::KeepAspectRatio));

    timerTitle.setObjectName("child");
    
    layout->addWidget(&timerTitle, 1, Qt::AlignCenter);
    layout->addWidget(imageLabel, 6, Qt::AlignCenter);
    layout->addWidget(&timer1Label, 1, Qt::AlignCenter);
    connect(&timer1, &QTimer::timeout, this, &TimerView::updateTimer1);
    
    MainWindow::clientManager->subscribe(title.toStdString(), resetTimer);
    timer1.start(1000);
}



void TimerView::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    QPixmap scaledPixmap = originalPixmap.scaled(imageLabel->size(), Qt::KeepAspectRatio);
    imageLabel->setPixmap(scaledPixmap);
}

void TimerView::updateTimer1() {
    ++timer1Count;
    timer1Label.setText(formatTime(timer1Count));
}

QString TimerView::formatTime(int seconds) {
    int minutes = seconds / 60;
    int remainingSeconds = seconds % 60;
    return QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(remainingSeconds, 2, 10, QChar('0'));
}



