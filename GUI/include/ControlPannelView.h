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
#include <QGridLayout>

#include "../../Server/ERT_RF_Protocol_Interface/PacketDefinition.h"

class ControlPannelView : public QFrame {
    Q_OBJECT

public:
    ControlPannelView(QWidget *parent = nullptr, QMap<std::string, QMap<std::string, std::vector<GUI_FIELD>>> *controls = nullptr);
    void resizeWidget();
    virtual ~ControlPannelView() {};

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void expandClicked();
    std::unique_ptr<QLabel> displayText;
    int getHeightPos();
    void setupExpandButton();
    void setupContainerWidget();
    void createValveControlButtons(QGridLayout *gridLayout, const std::vector<GUI_FIELD> &strings, int maxColumns);
    void createValveLayouts(QHBoxLayout *mainLayout, QMap<std::string, std::vector<GUI_FIELD>> *valves);
    void createPushButtonLayouts(QHBoxLayout *mainLayout, QMap<std::string, std::vector<GUI_FIELD>> *buttons);
    
    QPixmap buttonPixMap;
    bool toggled;
    QWidget *controlContainerWidget;
    QPushButton *expandButton;
};

#endif // CONTROLPANNELVIEW_H

