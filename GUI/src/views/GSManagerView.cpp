#include <memory>

#include <QLabel>
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

#include "GSManagerView.h"
#include "MainWindow.h"
#include "TimerView.h"
#include "../Setup.h"

GSManagerView::GSManagerView(std::unique_ptr<QWidget> parent) : QFrame(parent.get()) {
    // Set up the appearance or behavior as needed

    setStyleSheet("background-color: lightblue;");
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    setupUI();

}

void GSManagerView::setupUI() {
    // QPushButton  *reseButton = new QPushButton();
    std::unique_ptr<QLabel> label_timers = std::make_unique<QLabel>("Timers section");
    QLabel *label_serial = new QLabel("Serial section");
    QLabel *label_downrange = new QLabel("Downrange section + packet number");
    displayText = std::make_unique<QLabel>("test");
    displayText->setText("newtest");
    layout = new QVBoxLayout(this);
    MainWindow::clientManager->subscribe("test", setDisplayText);
    MainWindow::clientManager->handleReceivedData("{\"test\": \"value\"}");
   
   

    setupTimersSection();
    setupInfoSection();

    QWidget *wrapper = new QWidget; 
    QHBoxLayout *wrapperLayout = new QHBoxLayout(wrapper); 
    wrapperLayout->addWidget(timersSection, 1);
    wrapperLayout->addWidget(infoSection, 1);
    

    layout->addWidget(wrapper, 1);
    layout->addWidget(label_serial, 2);
    layout->addWidget(label_downrange, 1);
    layout->addWidget(displayText.get(), 1);
    layout->addStretch(20);

}

void GSManagerView::setupInfoSection() {

    QString cardStyle = QString(R"(background: qradialgradient(cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 %1, stop:0.5 %2);color: #B8C196;border-radius: 20px;
    )")
                    .arg("#21264a")
                    .arg(col::backgroundColorCode);
// qradialgradient(cx: 0.5, cy: 0.5, radius: 2, fx: 0.5, fy: 1, stop: 0 rgb(0, 0, 0) , stop: 0.4 rgb(255, 255, 255)); 

    QString childrenStyle = QString("background: rgba(0, 0, 0, 0)");
    infoSection = new QWidget; 

    // infoSection->setStyleSheet(col::background()+"border-radius: 20px; color: #B8C196");
    infoSection->setStyleSheet(cardStyle);
    QWidget *line = new QWidget;
    line->setFixedHeight(1);
    line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    line->setStyleSheet(QString("background-color: #c0c0c0;"));


    downRange = new QLabel("--");
    QFont font = downRange->font();
    font.setPointSize(27);
    downRange->setStyleSheet(childrenStyle);
    downRange->setFont(font);
    
    packetNumber = new QLabel("--");
    packetNumber->setStyleSheet(childrenStyle);

    QLabel *downRangeLabel = new QLabel("Downrange");
    downRangeLabel->setStyleSheet(childrenStyle);
    font = downRangeLabel->font();
    font.setPointSize(15);
    font.setBold(true);
    downRangeLabel->setFont(font);

    QLabel *packetNumberLabel = new QLabel("Packet Number");
    packetNumberLabel->setStyleSheet(childrenStyle);
    font = packetNumberLabel->font();
    font.setPointSize(15);
    font.setBold(true);
    packetNumberLabel->setFont(font);

    QVBoxLayout *infoLayout = new QVBoxLayout(infoSection);
    infoLayout->addWidget(downRangeLabel, 1);
    infoLayout->addWidget(downRange, 2);
    infoLayout->addStretch(1);
    infoLayout->addWidget(line);
    infoLayout->addWidget(packetNumberLabel, 1);
    infoLayout->addStretch(3);


}

void GSManagerView::setupTimersSection() {
    timerViewAV = new TimerView("AV");
    timerViewGSE = new TimerView("GSE");
    // layout->addWidget(label_timers.get(), 1);

    timersSection = new QWidget;
    QHBoxLayout *timersLayout = new QHBoxLayout(timersSection);
    timersLayout->addWidget(timerViewAV, 1);
    timersLayout->addWidget(timerViewGSE, 1);
}

