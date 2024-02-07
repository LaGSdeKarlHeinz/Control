
/** 
    @authors M.Rochat & E.Dutruy (Co-TL GS 23-24)
    @date 06-02-2024
    @brief Main function for the GUI
*/

#include <QApplication>
#include <QResource>

#include "MainWindow.h"
#include "ClientManager.h"
#include <QTimer>

void fakeDataHandling();

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);


    QResource::registerResource("/home/mrochat/ert/GUIV2/GUI/res/resources.rcc");
  
    MainWindow mainWindow;
    QTimer::singleShot(5000, fakeDataHandling);
    
    mainWindow.show();
    return app.exec();
}

void fakeDataHandling() {
    std::string jsonString = R"(
    {
  "name": "John",
  "age": 30,
  "isMarried": true,
  "children": ["Alice", "Bob"],
  "address": {
    "test": "123 Main St",
    "city": "Anytown",
    "zip": "12345",
    "coordinates": {
      "latitude": 40.7128,
      "longitude": -74.0060
    }
  },
  "contacts": [
    {
      "name": "Mary",
      "phone": "123-456-7890"
    },
    {
      "name": "Mike",
      "phone": "987-654-3210"
    }
  ]
})";


    MainWindow::clientManager->handleReceivedData(QString::fromStdString(jsonString)); // "{\"test\":\"data received!\"}"
}
