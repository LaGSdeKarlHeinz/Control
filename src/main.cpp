#include <iostream>

#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QFrame>
#include <DataView.h>

#include "GSManagerView.h"
#include "Server.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Create the main window
    QMainWindow mainWindow;

    // Create the main widget
    QWidget *centralWidget = new QWidget(&mainWindow);
    mainWindow.setCentralWidget(centralWidget);

    // Create layout for the central widget
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Create a horizontal layout for the two sections
    QHBoxLayout *sectionsLayout = new QHBoxLayout;



    // Create the left section (3/5)
    QFrame *leftSection = new QFrame;
    leftSection->setStyleSheet("background-color: lightblue;"); // Set your color
    leftSection->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    // Create the right section (2/5)
    QFrame *rightSection = new QFrame;
    rightSection->setStyleSheet("background-color: lightgreen;"); // Set your color
    rightSection->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        // Start the server
    Server *server = new Server(rightSection);
    if (!server->listen(QHostAddress::Any, 12345)) {

        std::cout << "server failed" << std::endl;
        qDebug() << "Unable to start server:" << server->errorString();
    } else {
        std::cout << "server started" << std::endl;
        qDebug() << "Server started on port 12345";
    }
    QFrame *rightSection2 = new GSManagerView;

    // Add the sections to the layout
    sectionsLayout->addWidget(leftSection, 3);
    sectionsLayout->addWidget(rightSection2, 2);

    // Add the sections layout to the main layout
    mainLayout->addLayout(sectionsLayout);

    // Set a uniform background color for the central widget
    centralWidget->setStyleSheet("background-color: lightgray;"); // Set your color

    // Set up the main window
    mainWindow.setGeometry(100, 100, 800, 600);
    mainWindow.show();

    return app.exec();
}
