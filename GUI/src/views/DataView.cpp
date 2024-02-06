/**
    @authors M.Rochat & E.Dutruy (Co-TL GS 23-24)
    @date 06-02-2024
    @brief QFrame displaying global data
*/

#include <memory>

#include <QLabel>
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "DataView.h"

DataView::DataView(std::unique_ptr<QWidget> parent) : QFrame(parent.get()) {
    
    // Set up the appearance or behavior as needed
    setStyleSheet("background-color: lightblue;");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    // Add a QLabel to display text
    displayText = std::make_unique<QLabel>("This is DataView");
    displayText->setAlignment(Qt::AlignCenter);
    
    std::unique_ptr<QHBoxLayout> layout = std::make_unique<QHBoxLayout>(this);

    layout->addWidget(displayText.get(), 2);
}