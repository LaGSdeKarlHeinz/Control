#include <iostream>

#include <QCoreApplication>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QTimer>

#include "Server.h"
#include "../ERT_RF_Protocol_Interface/PacketDefinition.h"



int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    
    Server server = Server();
    int port(12345);
    std::cout << "Server started" << std::endl;
    if (server.listen(QHostAddress::Any, port)) {
        std::cout << "Server started. Listening on port" << port << std::endl;
    } else {
        std::cout << "Error: Failed to start server. Check if the port is already in use or permissions issue." <<std::endl;      
    }

    QTimer *timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, &server, &Server::simulateJsonData);
    timer->start(2000); // Timer fires every 2000 milliseconds (2 seconds)

    QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();
    std::cout << "found " << availablePorts.size() << " devices" << std::endl;
    foreach(const QSerialPortInfo &portInfo, availablePorts) {
        std::cout << "Port name: " << portInfo.portName().toStdString() << std::endl;
        std::cout << "Description: " << portInfo.description().toStdString() << std::endl;
        std::cout << "Manufacturer: " << portInfo.manufacturer().toStdString() << std::endl;
    }
    std::cout << "setup finished" << std::endl;
    return a.exec();
}
