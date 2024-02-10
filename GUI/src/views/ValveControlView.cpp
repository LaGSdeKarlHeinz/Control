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



ValveControlView::ValveControlView(QWidget *parent) : QFrame(parent), backgroundImage(nullptr) {
    setContentsMargins(25, 25, 25, 25);
    setMinimumWidth(mws::middleSectionWidth / 100.0 * mws::width);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setSvgBackground(":/images/prop-diagram-firehorn.svg");
    addButtonIcon(0.226, 0.465);
    addButtonIcon(0.226, 0.55);
    addButtonIcon(0.226, 0.635, ValveButton::Orientation::Horizontal);
}

void ValveControlView::setSvgBackground(const QString& filePath) {
    // Load the SVG image
    QSvgRenderer svgRenderer(filePath);
    if (svgRenderer.isValid()) {
        // Calculate the scaled size while maintaining the aspect ratio
        int scaledWidth = svgRenderer.defaultSize().width();
        int scaledHeight = svgRenderer.defaultSize().height();

        // Calculate the offsets to center the image both horizontally and vertically
        int xOffset = 0; // Center horizontally
        int yOffset = 0; // Center vertically

        // Render the SVG onto a pixmap
        backgroundImage = std::make_unique<QPixmap>(scaledWidth, scaledHeight);
        backgroundImage->fill(Qt::transparent);
        QPainter painter(backgroundImage.get());
        svgRenderer.render(&painter, QRectF(xOffset, yOffset, scaledWidth, scaledHeight));
    }
}

void ValveControlView::addButtonIcon(float x, float y, ValveButton::Orientation orientation) {
    ValveButton *button = new ValveButton(orientation,this);
    Position pos; 
    pos.x = x; 
    pos.y = y;
    valvesMap.insert(button, pos);

    update(); // Trigger repaint to draw the new icon
}

void ValveControlView::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);

    // Ensure the background image is valid
    if (!backgroundImage) return;
    
    
    QPixmap scaledPixmap = backgroundImage->scaledToWidth(width() - contentsMargins().left() * 2);

    // Calculate the offsets to center the image horizontally and vertically
    int xOffset = (width() - scaledPixmap.width()) / 2;
    int yOffset = (height() - scaledPixmap.height()) / 2;

    // Draw the background image
    painter.drawPixmap(xOffset, yOffset, scaledPixmap);

    for (auto it = valvesMap.begin(); it != valvesMap.end(); ++it) {
        ValveButton* button = it.key();
        Position position = it.value();
        int xPos = scaledPixmap.width()*position.x - button->width()/2; 
        int yPos = scaledPixmap.height()*position.y- button->height()/2; 
        button->move(xOffset + xPos, yOffset + yPos);
}

    
}

