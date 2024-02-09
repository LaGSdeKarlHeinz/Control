/**
    @authors M.Rochat & E.Dutruy (Co-TL GS 23-24)
    @date 06-02-2024
    @brief Main window of the application
*/

#include <memory>

#include <QLabel>
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "Setup.h"
#include "MainWindow.h"
#include "components/DraggableButton.h"
#include "ControlPannelView.h"



MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle(mws::title);
    setGeometry(mws::x, mws::y, mws::width, mws::height);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setStyleSheet(col::background());
    
    QVBoxLayout *centralLayout = new QVBoxLayout(centralWidget);

    QHBoxLayout *sectionsLayout = createSectionsLayout();
    centralLayout->addLayout(sectionsLayout);

    
}



QHBoxLayout* MainWindow::createSectionsLayout() {
    QHBoxLayout *sectionsLayout = new QHBoxLayout();

    QFrame *leftSection = new LeftView();
    QFrame *middleSection = new MiddleView();
    QFrame *rightSection = new RightView();
    
    // Instantiate a QMap with std::string keys and std::vector<std::string> values
    QMap<std::string, std::vector<std::string>> valvesMap;
    QMap<std::string, std::vector<std::string>> pushButtonMap;
    QMap<std::string, QMap<std::string, std::vector<std::string>>> controlMap;

    // Populate the QMap with key-value pairs
    valvesMap.insert("Engine Valves", {"test 5", "test 6", "test 7", "test 8", "test 9"});
    valvesMap.insert("GSE Valves", {"test 1", "test 2", "test 3", "test 4"});
    
    pushButtonMap.insert("Command", {"Command 1", "Command 2", "Command 3"});
    controlMap.insert("ValveControlButton", valvesMap);
    controlMap.insert("QPushButton", pushButtonMap);

    pannelSection = new ControlPannelView(this, &controlMap);
    pannelSection->move(100, 300);

    replacePannelButton();



    sectionsLayout->addWidget(leftSection, (100-mws::middleSectionWidth)/2);
    sectionsLayout->addWidget(middleSection, mws::middleSectionWidth);
    sectionsLayout->addWidget(rightSection, (100-mws::middleSectionWidth)/2);
    

    return sectionsLayout;
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    replacePannelButton();    
    pannelSection->resizeWidget();
}

void MainWindow::replacePannelButton() {
    // QPoint p = QWidget::mapTo(this, QPoint(width()/2-pannelButton->width()/2, height()-pannelButton->height()));
    // pannelButton->move(p);
}

