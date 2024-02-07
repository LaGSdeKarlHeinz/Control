#include <memory>

#include <QLabel>
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

#include "GSManagerView.h"
#include "MainWindow.h"
#include "TimerView.h"

GSManagerView::GSManagerView(std::unique_ptr<QWidget> parent) : QFrame(parent.get()) {
    // Set up the appearance or behavior as needed

    setStyleSheet("background-color: lightblue;");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setupUI();

}

void GSManagerView::setupUI() {
    // QPushButton  *reseButton = new QPushButton();
    std::unique_ptr<QLabel> label_timers = std::make_unique<QLabel>("Timers section");
    QLabel *label_serial = new QLabel("Serial section");
    QLabel *label_downrange = new QLabel("Downrange section + packet number");
    displayText = std::make_unique<QLabel>("test");
    displayText->setText("newtest");
    QVBoxLayout *layout = new QVBoxLayout(this);
    MainWindow::clientManager->subscribe("test", setDisplayText);
    MainWindow::clientManager->handleReceivedData("{\"test\": \"value\"}");
    TimerView *timerView = new TimerView();
    // layout->addWidget(label_timers.get(), 1);
    layout->addWidget(timerView, 1);
    layout->addWidget(label_serial, 2);
    layout->addWidget(label_downrange, 1);
    layout->addWidget(displayText.get(), 1);
    layout->addStretch(20);

}


