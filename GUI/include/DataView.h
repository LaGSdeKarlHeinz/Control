/**
    @authors M.Rochat & E.Dutruy (Co-TL GS 23-24)
    @date 06-02-2024
    @brief QFrame displaying global data
*/

#ifndef DATAVIEW_H
#define DATAVIEW_H

#include <memory>

#include <QLabel>

class DataView : public QFrame {
    Q_OBJECT

public:
    DataView(std::unique_ptr<QWidget> parent = nullptr);
    
    virtual ~DataView() {};

private:
    std::unique_ptr<QLabel> displayText;
};

#endif // DATAWIDGET_H
