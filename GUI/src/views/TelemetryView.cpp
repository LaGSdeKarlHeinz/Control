/** 
    @authors M.Rochat & E.Dutruy (Co-TL GS 23-24)
    @date 06-02-2024
    @brief QFrame displaying telemetry data
*/

#include <memory>

#include <QLabel>
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "TelemetryView.h"

TelemetryView::TelemetryView(std::unique_ptr<QWidget> parent) : QFrame(parent.get()) {
    
    // Set up the appearance or behavior as needed
    //setStyleSheet("background-color: lightblue;");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    altitudeLabel = std::make_unique<QLabel>("Altitude");
    altitudeLabel->setAlignment(Qt::AlignCenter);

    std::unique_ptr<QHBoxLayout> layout = std::make_unique<QHBoxLayout>(this);

    layout->addWidget(altitudeLabel.get(), 2);
}