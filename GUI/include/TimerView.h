// TimerView.h
#ifndef TIMERVIEW_H
#define TIMERVIEW_H

#include <QWidget>
#include <QTimer>
#include <QPushButton>
#include <QLabel>
#include <memory>

class TimerView : public QWidget {
    Q_OBJECT
public:
    TimerView(QWidget *parent = nullptr);
    virtual ~TimerView() {}

signals:
    void customEventReceived(int eventType);

public slots:
    void handleCustomEvent(int eventType);

private slots:
    void updateTimer1();
    void updateTimer2();
    void resetTimer1();
    void resetTimer2();

private:
    QTimer timer1;
    QTimer timer2;
    QLabel timer1Label;
    QLabel timer2Label;
    QPushButton resetButton1;
    QPushButton resetButton2;
    int timer1Count;
    int timer2Count;
};

class CustomEvent {
public:
    CustomEvent(int type) : eventType(type) {}
    int getType() const { return eventType; }

private:
    int eventType;
};

class AVDataReceivedEvent : public CustomEvent {
public:
    AVDataReceivedEvent() : CustomEvent(1) {}
};

class GSEDataReceivedEvent : public CustomEvent {
public:
    GSEDataReceivedEvent() : CustomEvent(2) {}
};

#endif // TIMERVIEW_H