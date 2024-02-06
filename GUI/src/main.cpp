
/** 
    @authors M.Rochat & E.Dutruy (Co-TL GS 23-24)
    @date 06-02-2024
    @brief Main function for the GUI
*/

#include <QApplication>

#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
