#include <QLabel>
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

#include "GSManagerView.h"

GSManagerView::GSManagerView(QWidget *parent) : QFrame(parent) {
    // Set up the appearance or behavior as needed

    setStyleSheet("background-color: lightblue;");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setupUI();

}

void GSManagerView::setupUI() {
    // QPushButton  *reseButton = new QPushButton();
    QLabel *label_timers = new QLabel("Timers section");
    QLabel *label_serial = new QLabel("Serial section");
    QLabel *label_downrange = new QLabel("Downrange section + packet number");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(label_timers, 1);
    layout->addWidget(label_serial, 2);
    layout->addWidget(label_downrange, 1);
    layout->addStretch(20);

}

