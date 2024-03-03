#include "SerialView.h"
#include "MainWindow.h"
#include "../Setup.h"

SerialView::SerialView(std::unique_ptr<QWidget> parent) : QFrame(parent.get()) {
    setObjectName("SerialView");
    setStyleSheet(col::defaultCardStyle("SerialView") + "#SerialView {margin-left: 8px;margin-right:8px;}");
    
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    
    isOpen = false;
    layout = new QHBoxLayout(this);

    setupStatusLed();

    serialNameLabel = new QLabel(QString("Serial port used : %1").arg("-")); 
    serialNameLabel->setObjectName("child");

    openButton = new QPushButton; 
    openButton->setObjectName("child");
    openButton->setText("click");

    layout->addWidget(serialNameLabel, 1, Qt::AlignHCenter);
    layout->addWidget(openButton, 1);
    layout->addWidget(statusLed, 1, Qt::AlignHCenter);

    setupStyle();
    setupConnections();

}

void SerialView::buttonClicked() {
    if (isOpen) {
        MainWindow::clientManager->send("closeSerial");
        
        return;
    } 

    MainWindow::clientManager->send("openSerial");
    
    
}

void SerialView::setupStyle() {
    openButton->setFixedHeight(35);
    openButton->setObjectName("openButton");
    QString style = QString(R"(
        QPushButton#openButton {
        color: %4;
        font: bold 14px;
        background: %1;
        border:2px solid %1;
        border-radius: 10px;
        }
        QPushButton#openButton:hover {
            background-color: %3;     
            
        }
        QPushButton#openButton:pressed {
            background-color: %2!important;     
            border:2px solid %4;
        }
        
    )")
    .arg(col::complementary)
    .arg(col::backgroundColorCode)
    .arg(col::complementaryLighter)
    .arg(col::primary);
    openButton->setStyleSheet(style);
}


void SerialView::setupConnections() {
    connect(openButton, &QPushButton::clicked, this, &SerialView::buttonClicked);
    MainWindow::clientManager->subscribe(GUI_FIELD::SERIAL_STATUS, setSerialStatus);
    MainWindow::clientManager->subscribe(GUI_FIELD::SERIAL_NAME_USE, setSerialName);
    MainWindow::clientManager->send("getSerialStatus");
}

void SerialView::changeButtonStyle(bool targetStatus) {
    if (targetStatus) {
        openButton->setText("Open"); 
        return;
    } 
    openButton->setText("Close");
}

void SerialView::updateStatus(QString newStatus) {
    if (newStatus == "open") {
        isOpen = true;
        statusLed->setStyleSheet(ledGreenStyle);
        statusLed->setToolTip("The serial is open");
    } else if (newStatus == "close") {
        isOpen = false; 
        statusLed->setStyleSheet(ledRedStyle);
        statusLed->setToolTip("The serial is closed");
    } else if (newStatus == "unknown") {
        isOpen = false; 
        statusLed->setStyleSheet(ledYellowStyle);
        statusLed->setToolTip("The serial state is unkown");
    } else {
        throw std::runtime_error("Invalid argument passed in function \"SerialView::updateStatus\", expected \"open\" or \"close\"");
    }
    changeButtonStyle(!isOpen);
}

void SerialView::setupStatusLed() {
    statusLed = new QLabel;
    statusLed->setObjectName("statusLed");
    statusLed->setFixedSize(20, 20);
    
}