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
    std::function<void(const QString)> setDownRange = [this](const QString newText) { downRange->setText(newText); };
    std::function<void(const QString)> setPacketNumber = [this](const QString newText) { 
        // setInfoChildrenStyle(packetNumber, 27, false);
        packetNumber->setText(newText); 
        };
    void setInfoChildrenStyle(QFrame *child, int fontSize, bool isBold);
    void setupConnections();
    void setupInfoLayout(QLabel *downRangeLabel, QLabel *packetNumberLabel, QWidget *line);
    void setupSerialSection();

    QLabel *downRange; 
    QLabel *packetNumber;
    QVBoxLayout *layout;
    TimerView *timerViewAV;
    TimerView *timerViewGSE;
    QWidget *timersSection;
    QWidget *infoSection;
    QWidget *serialSection;
    QString childrenStyle = QString("background: transparent");

};

#endif // DATAWIDGET_H
