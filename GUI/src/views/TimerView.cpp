#include <QVBoxLayout>
#include <QPixmap>

#include "TimerView.h"



TimerView::TimerView(QWidget *parent) : QWidget(parent), timer1Count(0), timer2Count(0) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    timer1Label.setText("0");

    QPixmap pm("../../res/icons/clock-icon-white.png");


    layout->addWidget(&timer1Label);

    connect(&timer1, &QTimer::timeout, this, &TimerView::updateTimer1);


    timer1.start(1000);
}

void TimerView::updateTimer1() {
    ++timer1Count;
    timer1Label.setText(QString::number(timer1Count));
}



void TimerView::resetTimer1() {
    timer1Count = 0;
    timer1Label.setText("0");
}




