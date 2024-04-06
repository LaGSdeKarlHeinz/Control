
/** 
    @authors M.Rochat & E.Dutruy (Co-TL GS 23-24)
    @date 06-02-2024
    @brief Main function for the GUI
*/
#include <iostream>

#include <QApplication>
#include <QResource>

#include "MainWindow.h"
#include "ClientManager.h"
#include "Setup.h"
#include <QTimer>
#include <QJsonDocument>
#include <QtNetwork/QTcpSocket>
#include "RequestBuilder.h"

void fakeDataHandling();

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QResource::registerResource("../res/resources.rcc");


    MainWindow::clientManager = std::make_unique<ClientManager>();    
    MainWindow mainWindow;
    
    mainWindow.show();
    return app.exec();
}
