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

#include "MainWindow.h"

#include "components/DataLabel.h"
#include "../Setup.h"
#include "TelemetryView.h"

TelemetryView::TelemetryView(QWidget* parent) : QFrame(parent) {
    
    // Set up the appearance or behavior as needed
    //setStyleSheet("background-color: lightblue;");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);
    
    // addField(GUI_FIELD::DISCONNECT_ACTIVE);
    QList<GUI_FIELD> fields = {GUI_FIELD::DISCONNECT_ACTIVE, GUI_FIELD::CHAMBER_PRESSURE};
    createSection("Test", &fields);
}

void TelemetryView::createSection(QString title, QList<GUI_FIELD> *fields) {
    QLabel* l = new QLabel(title);
    l->setStyleSheet(QString("font-size: 14pt; color: %1;font-weight: 400;").arg(col::primary));
    QWidget *wrapper = new QWidget;
    QVBoxLayout* layoutField = new QVBoxLayout(wrapper);
    layoutField->addWidget(l);
    for (int i=0; i<fields->size(); i++) {
        addField(fields->at(i), layoutField);
    }
    wrapper->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    layoutField->setAlignment(Qt::AlignTop);

    layout->addWidget(wrapper);
}

void TelemetryView::addField(GUI_FIELD f, QLayout* layout) {

    QStringList parts = fieldUtil::enumToFieldName(f).toLower().split(" ");
    for (int i=0; i<parts.size(); i++) {
        QString word = parts[i];
        parts[i] = word.at(0).toUpper()+word.mid(1);
        
    }
    QLabel* l = new QLabel(parts.join(" ")+" : ");
    l->setStyleSheet(QString("color: %1;").arg(col::primary));
    QWidget *wrapper = new QWidget;
    QHBoxLayout* layoutField = new QHBoxLayout(wrapper);
    layoutField->addWidget(l);
    layoutField->addWidget(new DataLabel(f));
    layout->addWidget(wrapper);
    
}
