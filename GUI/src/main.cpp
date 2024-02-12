
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


    QResource::registerResource("../res/resources.rcc");
  
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
  "downrange": "228m",
  "serialNameUsed": "tty0",
  "serialStatus" : "open",
  "names": ["Alice", "Bob"],
  "address": {
    "street": "123 Main St",
    "city": "Anytown",
    "zip": "12345",
    "coordinates": {
      "test": 40.7128,
      "longitude": -74.0060
    }
  },
  "contacts": [
    {
      "packetNumber": "12",
      "phone": "123-456-7890"
    },
    {
      "serialStatus": "close",
      "phone": "987-654-3210"
    }
  ]
})";


    MainWindow::clientManager->handleReceivedData(QString::fromStdString(jsonString)); // "{\"test\":\"data received!\"}"
}
