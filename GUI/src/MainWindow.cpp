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
    
    sectionsLayout->addWidget(leftSection, (100-mws::middleSectionWidth)/2);
    sectionsLayout->addWidget(middleSection, mws::middleSectionWidth);
    sectionsLayout->addWidget(rightSection, (100-mws::middleSectionWidth)/2);

    return sectionsLayout;
}