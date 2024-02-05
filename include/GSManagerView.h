#ifndef GSMANAGERVIEW_H
#define GSMANAGERVIEW_H

#include <QLabel>

class GSManagerView : public QFrame {
    Q_OBJECT

public:
    GSManagerView(QWidget *parent = nullptr);
    
    virtual ~GSManagerView() {};

private:
    void setupUI(); 
    QLabel *displayText;
};

#endif // DATAWIDGET_H
