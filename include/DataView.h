#ifndef DATAVIEW_H
#define DATAVIEW_H

#include <QLabel>

class DataView : public QFrame {
    Q_OBJECT

public:
    DataView(QWidget *parent = nullptr);
    
    virtual ~DataView() {};

private:
    QLabel *displayText;
};

#endif // DATAWIDGET_H
