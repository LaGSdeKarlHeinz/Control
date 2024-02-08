/**
    @authors M.Rochat & E.Dutruy (Co-TL GS 23-24)
    @date 06-02-2024
    @brief QFrame displaying global data
*/

#ifndef CONTROLPANNELVIEW_H
#define CONTROLPANNELVIEW_H

#include <memory>

#include <QLabel>
#include <QPushButton>

class ControlPannelView : public QFrame {
    Q_OBJECT

public:
    ControlPannelView(QWidget *parent = nullptr);
    void resizeWidget();
    virtual ~ControlPannelView() {};

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void expandClicked();
    std::unique_ptr<QLabel> displayText;
    int getHeightPos();
    void setupExpandButton();

    QPixmap buttonPixMap;
    int borderOffset;
    bool toggled;
    QWidget *controlContainerWidget;
    QPushButton *expandButton;
};

#endif // CONTROLPANNELVIEW_H
