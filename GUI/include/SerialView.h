/**
    @authors M.Rochat & E.Dutruy (Co-TL GS 23-24)
    @date 06-02-2024
    @brief QFrame displaying Serial related section
*/

#ifndef SERIALVIEW_H
#define SERIALVIEW_H

#include <memory>

#include <QLabel>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "../src/Setup.h"

class SerialView : public QFrame {
    Q_OBJECT

public:
    // Remove the default argument from the constructor declaration
    SerialView(std::unique_ptr<QWidget> parent = nullptr); // No default argument here

    virtual ~SerialView() {};
    

    



private:
    

    std::function<void(const QString)> setSerialStatus = [this](const QString newText) { updateStatus(newText); };
    std::function<void(const QString)> setSerialName = [this](const QString newText) { serialNameLabel->setText(QString("Serial port used : %1").arg(newText)); };
    void changeButtonStyle(bool targetStatus);
    void setupStyle();
    void buttonClicked();
    void updateStatus(QString newStatus);
    void setupStatusLed();
    void setupConnections();
    

    std::unique_ptr<QLabel> displayText;
    QHBoxLayout *layout;
    bool isOpen;
    QLabel *statusLed;
    QLabel *serialNameLabel; 
    QPushButton *openButton;
    QString ledGreenStyle = QString(R"(
        #statusLed {
            background: green;
            border:2px solid %1;
            border-radius: 10px;
        }
    )").arg(col::primary); 
    QString ledRedStyle = QString(R"(
        #statusLed {
            background: red;
            border:2px solid %1;
            border-radius: 10px;
        }
    )").arg(col::primary); 
    QString ledYellowStyle = QString(R"(
        #statusLed {
            background: yellow;
            border:2px solid %1;
            border-radius: 10px;
        }
    )").arg(col::primary); 
};

#endif // SERIALVIEW_H