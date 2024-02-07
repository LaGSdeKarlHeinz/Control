#ifndef GSMANAGERVIEW_H
#define GSMANAGERVIEW_H

#include <QLabel>

class GSManagerView : public QFrame {
    Q_OBJECT

public:
    GSManagerView(std::unique_ptr<QWidget> parent = nullptr);
    
    virtual ~GSManagerView() {};

private:
    void setupUI(); 
    std::function<void(const QString)> setDisplayText = [this](const QString newText) { displayText->setText(newText); };


    std::unique_ptr<QLabel> displayText;

};

#endif // DATAWIDGET_H
