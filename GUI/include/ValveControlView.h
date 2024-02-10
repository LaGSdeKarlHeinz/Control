/**
    @authors M.Rochat & E.Dutruy (Co-TL GS 23-24)
    @date 06-02-2024
    @brief QFrame displaying plumbing diagram and valve control
**/

#ifndef VALVECONTROLVIEW_H
#define VALVECONTROLVIEW_H

#include <QFrame>
#include <memory>

#include <QMap>

#include "components/ValveControlButton.h"
#include "components/ValveButton.h"

struct Position {
        float x;
        float y;
    };

class ValveControlView : public QFrame {
    Q_OBJECT

public:

    

    ValveControlView(QWidget *parent = nullptr);
    virtual ~ValveControlView() {}

    void setSvgBackground(const QString& filePath);
    void addButtonIcon(float x, float y, ValveButton::Orientation orientation = ValveButton::Orientation::Vertical);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    std::unique_ptr<QPixmap> backgroundImage;
    QMap<ValveButton*, Position> valvesMap;
};

#endif // VALVECONTROLVIEW_H
