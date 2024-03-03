#include <iostream>
#include <thread> 

#include "components/ToggleButton.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QtConcurrent>
#include <MainWindow.h>

#include "../../Server/ERT_RF_Protocol_Interface/PacketDefinition.h"

ToggleButton::ToggleButton(GUI_FIELD fieldSensitivity, QWidget *parent) : QWidget(parent), m_checked(false), m_offset(0)
{
    m_state = Unknown;
    setFixedSize(60, 30); // Set a fixed size for the toggle button
    m_loadingMovie = new QMovie(this);
    m_loadingMovie->setFileName(":/gif/loading.gif");

    // Initialize the QTimer
    m_timer = new QTimer(this);
    m_timer->setInterval(10); // Set the interval to 10 milliseconds
    
    connect(m_timer, &QTimer::timeout, this, &ToggleButton::updateAnim); // Connect the timeout signal to the update slot  
    m_timer->start(); // Start the timer
    m_loadingMovie->start();
    MainWindow::clientManager->subscribe(fieldSensitivity, [this](const QString& message) {
        updateState(message);
    });

    connect(this, &ToggleButton::toggled, this, [this](bool checked) {
          // MainWindow::clientManager->send("command");
          // QtConcurrent::run([this](const QString& commande){MainWindow::clientManager->send("command");}, "command");
          std::thread([=]() { MainWindow::clientManager->send("command");   }).detach();
    }); 
}

void ToggleButton::updateState(const QString& res) {

        if (res == "open") {       
            m_state = Open;
            m_checked = true;
            update();
            toggleCallback();
        } else if (res == "close") {
            m_state = Close;
            m_checked = false;
            update();
            toggleCallback();
        } else {
            setUnknown();
        }
}

QSize ToggleButton::sizeHint() const
{
    return QSize(60, 30);
}

bool ToggleButton::isChecked() const
{
    return m_state == Open;
}

void ToggleButton::setChecked(bool checked)
{

    State newState = checked ? Open : Close;
    if (m_state != newState) {
        
        m_checked = checked;
        

        // Animate the toggle with default duration (200 milliseconds)
        animateToggle(200);
        setUnknown(); // Set the state to unknown to indicate that the state is being updated
        // Start or stop the loading movie
        if (m_state == Unknown) {
            m_loadingMovie->start();
        } else {
            m_loadingMovie->stop();
        }
        emit toggled(checked);
    }
}


void ToggleButton::toggleCallback() {
    m_offset = m_checked ? width() - height() : 0;
}

void ToggleButton::animateToggle(int duration)
{
    qreal endValue = m_checked ? width() - height() : 0;


    QPropertyAnimation *animation = new QPropertyAnimation(this, "offset");
    animation->setDuration(duration);
    animation->setStartValue(m_offset);
    animation->setEndValue(endValue);
    animation->start();

    connect(animation, &QPropertyAnimation::valueChanged, this, [this](const QVariant &value) {
        m_offset = value.toReal();
        update(); // Request a repaint
    });
}

void ToggleButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
   
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (m_state == Open) {
        painter.setBrush(QColor("#007AFF")); // Blue color when open
    } else if (m_state == Close) {
        painter.setBrush(QColor("#d1d1d1")); // Apple-like color when closed
    } else { // Unknown
        painter.setBrush(QColor("#808080")); // Light gray color when unknown
    }
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect(), 15, 15);

    // Draw the switch
    painter.setBrush(Qt::white);
    
    if (m_checked && m_loadingMovie->isValid() && m_loadingMovie->currentPixmap().isNull() == false) {
        // Draw the current frame of the loading movie if the button is checked
        painter.drawEllipse(m_offset, 0, height(), height());
       
    } else {
        // Draw the switch normally if the button is not checked or the loading movie is not valid
        painter.drawEllipse(m_offset, 0, height(), height());
    }
    if (m_state == Unknown) {
        painter.drawPixmap(m_offset+2, 2, height()-4, height()-4, m_loadingMovie->currentPixmap());
    }
}

void ToggleButton::setUnknown()
{
    
        m_state = Unknown;
    
}

void ToggleButton::updateAnim()
{
    if (m_state == Unknown) {
        update();
    }
    
}

void ToggleButton::mousePressEvent(QMouseEvent *event)
{
    
    if (event->button() == Qt::LeftButton) {
        setChecked(!m_checked);
    }
}

qreal ToggleButton::offset() const {
    return m_offset;
}

void ToggleButton::setOffset(qreal offsetValue) {
    m_offset = offsetValue;
}
