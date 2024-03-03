// TimerView.h
#ifndef TIMERVIEW_H
#define TIMERVIEW_H

#include <QWidget>
#include <QTimer>
#include <QPushButton>
#include <QLabel>
#include <memory>

#include "../../Server/ERT_RF_Protocol_Interface/PacketDefinition.h"

class TimerView : public QWidget {
    Q_OBJECT
public:
    
    TimerView(QString title, GUI_FIELD field, QWidget *parent = nullptr);

    virtual ~TimerView() {}

private slots:
    void updateTimer1();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QTimer timer1;
    
    std::function<void(const QJsonValue&)> resetTimer = [this](const QJsonValue& json) { timer1Count=-1; updateTimer1(); };


    QLabel timer1Label;
    QLabel timerTitle;

    int timer1Count;
    
    QLabel *imageLabel;
    QPixmap originalPixmap;

    
    QString formatTime(int seconds);

};


#endif // TIMERVIEW_H