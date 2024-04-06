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



#include "components/DataLabel.h"
#include "../Setup.h"
#include "TelemetryView.h"

TelemetryView::TelemetryView(QWidget* parent) : QFrame(parent) {
    
    // Set up the appearance or behavior as needed
    //setStyleSheet("background-color: lightblue;");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        
    altitudeLabel = std::make_unique<QLabel>("Altitude");
    altitudeLabel->setAlignment(Qt::AlignCenter);

    layout = new QVBoxLayout(this);


    layout->addWidget(altitudeLabel.get(), 2);
    DataLabel* label = new DataLabel(GUI_FIELD::CHAMBER_PRESSURE, this);
    QLabel* label2 = new QLabel("Test");
    layout->addWidget(label2, 3);
    
    addField(GUI_FIELD::DISCONNECT_ACTIVE);
}

void TelemetryView::addField(GUI_FIELD f) {
    QStringList parts = fieldUtil::enumToFieldName(f).toLower().split(" ");
    for (int i=0; i<parts.size(); i++) {
        QString word = parts[i];
        parts[i] = word.at(0).toUpper()+word.mid(1);
    }
    QLabel* l = new QLabel(parts.join(" ")+" : ");
    QWidget *wrapper = new QWidget;
    QHBoxLayout* layoutField = new QHBoxLayout(wrapper);
    layoutField->addWidget(l);
    layoutField->addWidget(new DataLabel(f));
    layout->addWidget(wrapper);
}
