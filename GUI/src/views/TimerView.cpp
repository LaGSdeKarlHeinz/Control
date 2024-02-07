#include <QVBoxLayout>

#include "TimerView.h"


TimerView::TimerView(QWidget *parent) : QWidget(parent), timer1Count(0), timer2Count(0) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    timer1Label.setText("0");
    timer2Label.setText("0");
    resetButton1.setText("Reset Timer 1");
    resetButton2.setText("Reset Timer 2");

    connect(&resetButton1, &QPushButton::clicked, this, &TimerView::resetTimer1);
    connect(&resetButton2, &QPushButton::clicked, this, &TimerView::resetTimer2);
    connect(this, &TimerView::customEventReceived, this, &TimerView::handleCustomEvent);

    layout->addWidget(&timer1Label);
    layout->addWidget(&resetButton1);
    layout->addWidget(&timer2Label);
    layout->addWidget(&resetButton2);

    connect(&timer1, &QTimer::timeout, this, &TimerView::updateTimer1);
    connect(&timer2, &QTimer::timeout, this, &TimerView::updateTimer2);

    timer1.start(1000);
    timer2.start(1000);
}

void TimerView::updateTimer1() {
    ++timer1Count;
    timer1Label.setText(QString::number(timer1Count));
}

void TimerView::updateTimer2() {
    ++timer2Count;
    timer2Label.setText(QString::number(timer2Count));
}

void TimerView::resetTimer1() {
    timer1Count = 0;
    timer1Label.setText("0");
}

void TimerView::resetTimer2() {
    timer2Count = 0;
    timer2Label.setText("0");
}

void TimerView::handleCustomEvent(int eventType) {
    switch (eventType) {
        case 1:
            resetTimer1();
            break;
        case 2:
            resetTimer2();
            break;
        default:
            break;
    }
}
