
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
#include <QTimer>
#include <QtNetwork/QTcpSocket>

void fakeDataHandling();

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);



    // Create a TCP socket
    QTcpSocket socket;

    // Connect to the server
    socket.connectToHost("127.0.0.1", 12345); // Assuming the server is running on localhost (127.0.0.1) and listening on port 12345

    std::cout << "check connection" << std::endl;
    if (socket.waitForConnected()) {
        std::cout << "connected" << std::endl;

        // Send data to the server
        QByteArray data = "Hello, Server!";
        socket.write(data);
        socket.flush(); // Ensure that the data is sent immediately

        

        // Close the connection
        socket.close();
    } else {
        qDebug() << "Error: Failed to connect to the server.";
    }
    std::cout << "end" << std::endl;


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
