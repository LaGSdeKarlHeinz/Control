#ifndef TOGGLEBUTTON_H
#define TOGGLEBUTTON_H

#include <QWidget>

class ToggleButton : public QWidget
{   
    Q_PROPERTY(qreal offset READ offset WRITE setOffset)
    Q_OBJECT
public:
    explicit ToggleButton(QWidget *parent = nullptr);

    QSize sizeHint() const override;

    bool isChecked() const;
    void setChecked(bool checked);

    void animateToggle(int duration);

signals:
    void toggled(bool checked);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    bool m_checked;
    qreal m_offset;
    qreal offset() const;
    void setOffset(qreal offsetValue);
};

#endif // TOGGLEBUTTON_H
