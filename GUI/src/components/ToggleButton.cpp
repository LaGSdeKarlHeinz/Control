#include "components/ToggleButton.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPropertyAnimation>

ToggleButton::ToggleButton(QWidget *parent) : QWidget(parent), m_checked(false), m_offset(0)
{
    setFixedSize(60, 30); // Set a fixed size for the toggle button
}

QSize ToggleButton::sizeHint() const
{
    return QSize(60, 30);
}

bool ToggleButton::isChecked() const
{
    return m_checked;
}

void ToggleButton::setChecked(bool checked)
{
    if (m_checked != checked) {
        m_checked = checked;
        emit toggled(m_checked);

        // Animate the toggle with default duration (200 milliseconds)
        animateToggle(200);
    }
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

    // Draw the background
    if (m_checked) {
        painter.setBrush(QColor("#007AFF")); // Blue color when checked
    } else {
        painter.setBrush(QColor("#d1d1d1")); // Apple-like color when not checked
    }
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect(), 15, 15);

    // Draw the switch
    painter.setBrush(Qt::white);
    painter.drawEllipse(m_offset, 0, height(), height());
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
