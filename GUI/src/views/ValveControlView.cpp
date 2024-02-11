/**
    @authors M.Rochat & E.Dutruy (Co-TL GS 23-24)
    @date 06-02-2024
    @brief QFrame displaying global data
*/
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

#include <QPushButton>
#include <QPainter>
#include <QtSvg/QSvgRenderer>

#include "ValveControlView.h"
#include "../Setup.h"
#include "components/ValveButton.h"
#include "components/DraggableButton.h"
#include "components/DataLabel.h"



ValveControlView::ValveControlView(QWidget *parent) : QFrame(parent), backgroundImage(nullptr) {
    setContentsMargins(25, 25, 25, 25);
    setMinimumWidth(mws::middleSectionWidth / 100.0 * mws::width);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setSvgBackground(":/images/prop-diagram-firehorn-highres.png");
    placeValves();
    placeCommandButtons();
    placeDataLabels();
    DraggableButton *dButton = new DraggableButton(this);
    
}

void ValveControlView::placeValves() {
    
    // GSE Valves
    addButtonIcon(0.224152, 0.463284);
    addButtonIcon(0.226, 0.55);
    addButtonIcon(0.226, 0.635, ValveButton::Orientation::Horizontal);

    //Vent Valves
    addButtonIcon(0.605, 0.3825, ValveButton::Orientation::Horizontal);
    addButtonIcon(0.925, 0.3825, ValveButton::Orientation::Horizontal);
    // Pressure Valves
    addButtonIcon(0.7025, 0.297, ValveButton::Orientation::Vertical);
    addButtonIcon(0.8218, 0.297, ValveButton::Orientation::Vertical);
    // Engine valves
    addButtonIcon(0.717, 0.66555, ValveButton::Orientation::Horizontal);
    addButtonIcon(0.8072, 0.66555, ValveButton::Orientation::Horizontal);
    // Active Cooling valves
    addButtonIcon(0.6775, 0.725, ValveButton::Orientation::Vertical);
    addButtonIcon(0.84305, 0.725, ValveButton::Orientation::Vertical);

}

void ValveControlView::addDataLabel(const QString& field, float x, float y) {
    DataLabel *label = new DataLabel(field, this);
    addComponent(label, x, y);
}

void ValveControlView::placeDataLabels() {
    //GSE top
    addDataLabel("dataField", 0.0471464, 0.0934579);
    addDataLabel("dataField", 0.044665, 0.190921);
    //GSE bottom
    addDataLabel("dataField", 0.0587262, 0.546061);

    //N2O top pressure   
    addDataLabel("dataField", 0.609595, 0.178905);

    //Engine tank pressure
    addDataLabel("dataField", 0.55335, 0.473965);
    addDataLabel("dataField", 0.944582, 0.473965);

    // Engine left pressure 
    addDataLabel("dataField",  0.540116, 0.785047);
    addDataLabel("dataField", 0.540116, 0.867824);
    addDataLabel("dataField", 0.540116, 0.94526);

    // Engine right pressure
    addDataLabel("dataField", 0.924731, 0.783712);
    addDataLabel("dataField",0.924731, 0.87984);

}

void ValveControlView::placeCommandButtons() {
    addCommandButton("Pressurize",0.757651, -0.0440587);
    addCommandButton("Ignition",  0.760132, 1.03338);
    addCommandButton("Disconnect", 0.409429, 0.863818);
}


void ValveControlView::addCommandButton(const QString& label, float x, float y) {
    QPushButton *button = new QPushButton(label, this);
    button->setObjectName("commandButton");
    QString style = QString(R"(
        #%5 {
        color: %4;
        font: bold 14px;
        background: %1;
        border:2px solid %1;
        border-radius: 10px;
        padding-left: 20px;
        padding-right: 20px;
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
        .arg("commandButton");
    button->setStyleSheet(style);
    button->setFixedHeight(40);
    button->setContentsMargins(20,5, 20, 5);
    addComponent(button, x, y);
}

void ValveControlView::setSvgBackground(const QString& filePath) {
    // Load the SVG image
    backgroundImage = std::make_unique<QPixmap>(filePath);
}

void ValveControlView::addButtonIcon(float x, float y, ValveButton::Orientation orientation) {
    ValveButton *button = new ValveButton(orientation,this);
    
    addComponent(button, x, y);
 
    //update(); // Trigger repaint to draw the new icon
}

void ValveControlView::addComponent(QWidget* component, float x, float y) {
    Position pos; 
    pos.x = x; 
    pos.y = y;
    componentsMap.insert(component, pos);
}

void ValveControlView::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    // painter.setCompositionMode(QPainter::CompositionMode_Source);
    // Ensure the background image is valid
    if (!backgroundImage) return;
    
    
    QPixmap scaledPixmap = backgroundImage->scaledToWidth(width() - contentsMargins().left() * 2, Qt::SmoothTransformation);

    // Calculate the offsets to center the image horizontally and vertically
    int xOffset = (width() - scaledPixmap.width()) / 2;
    int yOffset = (height() - scaledPixmap.height()) / 2;
    // std::cout << yOffset << std::endl;
    // std::cout << scaledPixmap.width() << std::endl;
    // std::cout << scaledPixmap.height() << std::endl;
    // Draw the background image
    painter.drawPixmap(xOffset, yOffset, scaledPixmap);

    for (auto it = componentsMap.begin(); it != componentsMap.end(); ++it) {
        QWidget* button = it.key();
        Position position = it.value();
        int xPos = scaledPixmap.width()*position.x - button->width()/2; 
        int yPos = scaledPixmap.height()*position.y- button->height()/2; 
        button->move(xOffset + xPos, yOffset + yPos);
    }

    
}

