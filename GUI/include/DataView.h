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
