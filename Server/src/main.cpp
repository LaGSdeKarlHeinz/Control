#include <iostream>

#include <QCoreApplication>

#include "Server.h"

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
    
    return a.exec();
}