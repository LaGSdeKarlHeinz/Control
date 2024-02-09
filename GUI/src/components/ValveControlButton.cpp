#include <iostream>

#include "components/ValveControlButton.h"
#include <QHBoxLayout>
#include <QPixmap>
#include <QMouseEvent>
#include <QTimer>

#include "../Setup.h"

RefreshLabel::RefreshLabel(const QString &text, QWidget *parent) : QLabel(text, parent) {
    setObjectName("refreshButton");
    

    resetStyle();
    // icon from icons8 : https://icones8.fr/icon/123373/mettre-%C3%A0-jour-la-rotation-%C3%A0-gauche
    QPixmap buttonPixMap(":/icons/refresh-icon.png");
    setScaledContents(false); 
    setFixedHeight(40);
    setFixedWidth(40);
    setPixmap(buttonPixMap);
    setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

void RefreshLabel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        setStyleSheet(QString(R"(
            #refreshButton {
                background:transparent;
                border-radius: 10%;
            }
            #refreshButton:hover {
                background: rgba(90, 90, 90, 130);
            }
            
        )"));
        QTimer::singleShot(100,  [this]() {
            this->resetStyle();
        });
        emit clicked();
}

void RefreshLabel::resetStyle() {
    setStyleSheet(QString(R"(
            #refreshButton {
                background:transparent;
                border-radius: 10%;
            }
            #refreshButton:hover {
                background: rgba(90, 90, 90, 90);
            }
            
        )"));
}

ValveControlButton::ValveControlButton(const QString &title, QWidget *parent) : QWidget(parent)
{
    setStyleSheet("background: transparent;");
    
    // Create the title label
    QLabel *titleLabel = new QLabel(title, this);
    titleLabel->setAlignment(Qt::AlignLeft);
    titleLabel->setStyleSheet(QString("color:%1").arg(col::primary));
    QFont font = titleLabel->font();
    font.setPointSize(10);
    font.setBold(true);
    titleLabel->setFont(font);

    toggleButton = new ToggleButton(this);
    refreshLabel = new RefreshLabel(":/icons/up-arrow.png", this);


    // Set up layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(titleLabel);
    
    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(toggleButton);
    buttonsLayout->addWidget(refreshLabel);
    
    mainLayout->addLayout(buttonsLayout);
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    
    setLayout(mainLayout);

    connect(toggleButton, &ToggleButton::toggled, this, &ValveControlButton::valveToggled);
    connect(refreshLabel, &RefreshLabel::clicked, this, &ValveControlButton::refreshClicked);
    refreshLabel->setCursor(Qt::PointingHandCursor); // Change cursor to hand cursor for hover effect
}

QSize ValveControlButton::sizeHint() const
{
    return QSize(120, 60); // Adjust the height to accommodate the title label and buttons
}

bool ValveControlButton::isValveOpen() const
{
    return toggleButton->isChecked();
}



void ValveControlButton::setValveOpen(bool open)
{
    toggleButton->setChecked(open);
}

