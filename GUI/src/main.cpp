#include <iostream>

#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QFrame>

#include "DataView.h"
#include "TelemetryView.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Create the main window
    QMainWindow mainWindow;

    // Create the main widget
    QWidget *centralWidget = new QWidget(&mainWindow);
    mainWindow.setCentralWidget(centralWidget);
    centralWidget->setStyleSheet("background-color: lightgray;"); // Set your color

    // Create layout for the central widget
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Create a horizontal layout for the two sections
    QHBoxLayout *sectionsLayout = new QHBoxLayout;

    // Create the left section (3/5)
    QFrame *leftSection = new QFrame;
    leftSection->setStyleSheet("background-color: lightblue;"); // Set your color
    leftSection->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    // Create the right section (2/5)
    QFrame *rightSection = new DataView;

    // Add the sections to the layout
    sectionsLayout->addWidget(leftSection, 3);
    sectionsLayout->addWidget(rightSection, 2);

    // Add the sections layout to the main layout
    mainLayout->addLayout(sectionsLayout);

    // Set up the main window
    mainWindow.setGeometry(100, 100, 800, 600);
    mainWindow.show();

    return app.exec();
}
