#ifndef VALVEBUTTON_H
#define VALVEBUTTON_H

#include <QPushButton>
#include <QLabel>

class ValveButton : public QLabel {
    Q_OBJECT

public:
    enum State {
        Open = 0,
        Close,
        Unknown
    };

    enum Orientation { 
        Horizontal = 0,
        Vertical
    };

    explicit ValveButton(Orientation orientation = Horizontal, QWidget *parent = nullptr);
    void resetStyle();
    State getState();
    void setState(State state);

signals:
    void clicked();

private:
    State currentState;

    void updateButtonIcon();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    Orientation orientation;
    QSize iconSize;


};

#endif // VALVEBUTTON_H
