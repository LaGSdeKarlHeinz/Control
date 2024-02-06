/** 
    @authors M.Rochat & E.Dutruy (Co-TL GS 23-24)
    @date 06-02-2024
    @brief QFrame displaying telemetry data
*/

#ifndef TELEMETRYVIEW_H
#define TELEMETRYVIEW_H

#include <memory>

#include <QLabel>

class TelemetryView : public QFrame {
    Q_OBJECT

public:
    TelemetryView(std::unique_ptr<QWidget> parent = nullptr);
    
    virtual ~TelemetryView() {};

private:
    std::unique_ptr<QLabel> altitudeLabel;
};

#endif /* TELEMETRYVIEW_H */
