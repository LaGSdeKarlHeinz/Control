/**
    @authors M.Rochat & E.Dutruy (Co-TL GS 23-24)
    @date 06-02-2024
    @brief QFrame displaying global data
*/

#include <memory>
#include <iostream>
#include <algorithm>

#include <QLabel>
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QMatrix2x2>
#include <QGridLayout>

#include "ControlPannelView.h"
#include "components/ToggleButton.h"
#include "components/ValveControlButton.h"
#include "../Setup.h"
#include "MainWindow.h"
#include "RequestBuilder.h"

ControlPannelView::ControlPannelView(QWidget *parent,QMap<std::string, QMap<std::string, std::vector<GUI_FIELD>>> *controls) : QFrame(parent) {
    
    setStyleSheet("background:transparent;");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    toggled = false;
    // Add a QLabel to display text
    displayText = std::make_unique<QLabel>("This is DataView");
    displayText->setAlignment(Qt::AlignCenter);
    
    setupExpandButton();
    setupContainerWidget();
   



 

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(expandButton, 1, Qt::AlignCenter); 
    layout->addWidget(controlContainerWidget, 1, Qt::AlignCenter);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
   
    
    QHBoxLayout *containerLayout = new QHBoxLayout(controlContainerWidget);
    QMap<std::string, std::vector<GUI_FIELD>> valveControls = controls->value("ValveControlButton");
    createValveLayouts(containerLayout, &valveControls);
    QMap<std::string, std::vector<GUI_FIELD>> pushButtonControls = controls->value("QPushButton");
    createPushButtonLayouts(containerLayout, &pushButtonControls);
    
    containerLayout->setContentsMargins(20, 10, 20, 10);
    controlContainerWidget->setFixedHeight(240);    
    
    connect(expandButton, &QPushButton::clicked, this, &ControlPannelView::expandClicked);
    
    resizeWidget();
    
}

void ControlPannelView::createValveLayouts(QHBoxLayout *mainLayout, QMap<std::string, std::vector<GUI_FIELD>> *valves)
{

    for (auto it = valves->constBegin(); it != valves->constEnd(); ++it) {
        const QString &title = QString::fromStdString(it.key());
        int maxColumns = std::ceil(it.value().size() / 2.0);
        const std::vector<GUI_FIELD> &valveNames = it.value();

        QVBoxLayout *controlLayout = new QVBoxLayout;
        QLabel *titleLabel = new QLabel(title);
        QFont font = titleLabel->font();
        font.setPointSize(12);
        font.setBold(true);
        titleLabel->setFont(font);
        titleLabel->setStyleSheet(QString("color:%1").arg(col::primary));
        controlLayout->addWidget(titleLabel, 1, Qt::AlignLeft);

        QGridLayout *gridLayout = new QGridLayout;
        createValveControlButtons(gridLayout, valveNames, maxColumns);
        controlLayout->addLayout(gridLayout, 4);

        mainLayout->addLayout(controlLayout);
    }
}

void ControlPannelView::createPushButtonLayouts(QHBoxLayout *mainLayout, QMap<std::string, std::vector<GUI_FIELD>> *buttons)
{
    
    for (auto it = buttons->constBegin(); it != buttons->constEnd(); ++it) {
    
        const QString &title = QString::fromStdString(it.key());
        const std::vector<GUI_FIELD> &buttonField = it.value();
        
        QVBoxLayout *controlLayout = new QVBoxLayout;
        QLabel *titleLabel = new QLabel(title);
       
        titleLabel->setFixedHeight(37);
        titleLabel->setStyleSheet(QString("color:%1;").arg(col::primary));
        QFont font = titleLabel->font();
        font.setPointSize(13);
        font.setBold(true);
        titleLabel->setFont(font);
        controlLayout->addWidget(titleLabel, 1, Qt::AlignLeft);
        controlLayout->setSpacing(15);
        QGridLayout *gridLayout = new QGridLayout;
        gridLayout->setSpacing(25);
        int maxColumns = std::ceil(buttonField.size() / 2.0);

        


        for (int i = 0; i < buttonField.size(); ++i) {
            std::string trimmedName = fieldUtil::enumToFieldName(buttonField[i]).toStdString();
            QPushButton *button = new QPushButton(fieldUtil::enumToFieldName(buttonField[i]));
            std::replace(trimmedName.begin(), trimmedName.end(), ' ', '_');
            
            button->setObjectName(QString::fromStdString(trimmedName));
            QString style = QString(R"(
                #%5 {
                color: %4;
                font: bold 14px;
                background: %1;
                border:2px solid %1;
                border-radius: 10px;
                }
                #%5:hover {
                    background-color: %3;     
                    
                }
                #%5:pressed {
                    background-color: %2!important;     
                    border:2px solid %4;
                }   
                )")
                .arg(col::complementary)
                .arg(col::backgroundColorCode)
                .arg(col::complementaryLighter)
                .arg(col::primary)
                .arg(QString::fromStdString(trimmedName));

            QObject::connect(button, &QPushButton::clicked, [button]() {
                // printf("fdsf");
                RequestBuilder b;
                b.setHeader(RequestType::POST);
                b.addField("cmd", button->text());
                b.addField("cmd_order", "1");
                MainWindow::clientManager->send(b.toString());
            });

            
            button->setFixedHeight(40);
            button->setStyleSheet(style);
            gridLayout->addWidget(button, i / maxColumns, i % maxColumns);
        }

        controlLayout->addLayout(gridLayout, 4);
        controlLayout->setAlignment(Qt::AlignTop);
        

        mainLayout->addLayout(controlLayout, Qt::AlignBottom);
        // mainLayout->addWidget(w, Qt::AlignTop);
    }
}


void ControlPannelView::buttonClickedCallback(const std::string& command) {
    printf("command");
    
}

void ControlPannelView::createValveControlButtons(QGridLayout *gridLayout, const std::vector<GUI_FIELD> &fields, int maxColumns)
{
    // Clear existing items from the grid layout
    QLayoutItem *child;
    while ((child = gridLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    // Set the maximum number of columns based on the desired width
     // Set the desired number of columns
    gridLayout->setColumnStretch(maxColumns, 1);

    int row = 0;
    int column = 0;

    // Add ValveControlButton for each string
    for (const GUI_FIELD &field : fields) {
        ValveControlButton *button = new ValveControlButton(field);
        gridLayout->addWidget(button, row, column);

        // Move to the next row or wrap to the next column
        if (++column == maxColumns) {
            column = 0;
            ++row;
        }
    }
}

void ControlPannelView::setupContainerWidget() {

    controlContainerWidget = new QWidget(this);
    controlContainerWidget->setObjectName("controlPannel");
    QString controlPannelStyle = QString(R"(
        #controlPannel {
            
            border-top-left-radius: 10%;
            border-top-right-radius: 10%;

        }
    )");
    controlContainerWidget->setStyleSheet(col::defaultCardStyle("controlPannel") + controlPannelStyle);
}

void ControlPannelView::resizeEvent(QResizeEvent *event) {
    resizeWidget();    
}

void ControlPannelView::setupExpandButton() {

    expandButton = new QPushButton(this);
    expandButton->setObjectName("expandButton");
    QString buttonStyle = QString(R"(
        #expandButton {
            background: %1;
            border-top-left-radius: 10%;
            border-top-right-radius: 10%;
        }
    )")
    .arg(col::complementary);
    expandButton->setStyleSheet(buttonStyle);

    // button icon : https://icones8.fr/icon/7LmItvRdpSjs/up-arrow
    buttonPixMap = QPixmap(":/icons/up-arrow.png");
   
    QIcon buttonIcon(buttonPixMap);
    
    expandButton->setFixedHeight(35);
    expandButton->setIcon(buttonIcon);
    expandButton->setIconSize(QSize(64, 64));
    
    

}


void ControlPannelView::resizeWidget() {
    int windowWidth = parentWidget()->width();
    int newWidth(windowWidth*mws::middleSectionWidth/100);
    int newHeight(controlContainerWidget->height() + expandButton->height());
    setFixedWidth(newWidth);
    
    move(QPoint((windowWidth-newWidth)/2, getHeightPos()));
    // Set a minimum height to ensure visibility
    setFixedHeight(newHeight);    

    QPoint p = QWidget::mapTo(this, QPoint(width()/2-expandButton->width()/2, 0));
    
    controlContainerWidget->setFixedWidth(newWidth);
    //controlContainerWidget->move(0, expandButton->height());
}

void ControlPannelView::expandClicked() {
    toggled = !toggled;
    QPropertyAnimation* anim = new QPropertyAnimation(this, "pos");
	anim->setDuration(1000);
	anim->setEasingCurve(QEasingCurve::Type::OutQuart);
	anim->setStartValue(pos());
	anim->setEndValue(QPoint(pos().x(), getHeightPos()));
	anim->start(QAbstractAnimation::DeleteWhenStopped);
    QTransform transform;
    buttonPixMap = buttonPixMap.transformed(transform.rotate(180));
    QIcon buttonIcon(buttonPixMap);    
    expandButton->setFixedHeight(35);
    expandButton->setIcon(buttonIcon);
    expandButton->setIconSize(QSize(64, 64));
    
    // resizeWidget();
}

int ControlPannelView::getHeightPos() {
    int windowWidth = parentWidget()->width();
    int newHeight(controlContainerWidget->height() + expandButton->height());
    int newY;
    if (toggled) {
        newY = parentWidget()->height()-newHeight;

    } else {
        newY = parentWidget()->height()-expandButton->height();
        
    }
    
    return newY;
}