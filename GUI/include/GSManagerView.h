#ifndef GSMANAGERVIEW_H
#define GSMANAGERVIEW_H

#include <QLabel>
#include <QVBoxLayout>

#include "TimerView.h"

class GSManagerView : public QFrame {
    Q_OBJECT

public:
    GSManagerView(std::unique_ptr<QWidget> parent = nullptr);
    
    virtual ~GSManagerView() {};

private:
    void setupUI(); 
    void setupInfoSection();
    void setupTimersSection();
    std::function<void(const QString)> setDisplayText = [this](const QString newText) { displayText->setText(newText); };


    std::unique_ptr<QLabel> displayText;
    QLabel *downRange; 
    QLabel *packetNumber;
    QVBoxLayout *layout;
    TimerView *timerViewAV;
    TimerView *timerViewGSE;
    QWidget *timersSection;
    QWidget *infoSection;

};

#endif // DATAWIDGET_H
