#ifndef VALVECONTROLBUTTON_H
#define VALVECONTROLBUTTON_H

#include <QWidget>
#include <QLabel>
#include "ToggleButton.h"

class CLickableIcon : public QLabel
{
    Q_OBJECT
public:
    CLickableIcon(const QString &text, QWidget *parent = nullptr);
    void resetStyle();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    
};

class ValveControlButton : public QWidget
{
    Q_OBJECT
public:
    explicit ValveControlButton(GUI_FIELD valveField, QWidget *parent = nullptr);

    QSize sizeHint() const override;

    bool isValveOpen() const;
    void setValveOpen(bool open);

    QIcon buttonIcon() const;
    void setButtonIcon(const QIcon &icon);
    
signals:
    void valveToggled(bool open);
    void refreshClicked();

private:
    ToggleButton *toggleButton;
    CLickableIcon *refreshLabel;
    
    
};

#endif // VALVECONTROLBUTTON_H
