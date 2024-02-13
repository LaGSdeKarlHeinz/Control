#include "Server.h"
#include <iostream>

Server::Server(QObject *parent) : QTcpServer(parent) {
}

void Server::incomingConnection(qintptr socketDescriptor) {
    // A new connection is incoming
    QTcpSocket *client = new QTcpSocket(this);
    client->setSocketDescriptor(socketDescriptor);

    connect(client, &QTcpSocket::readyRead, this, &Server::readyRead);
    connect(client, &QTcpSocket::disconnected, this, &Server::disconnected);

    clients.append(client);

    std::cout << "Client connected: " << socketDescriptor << std::endl;
}


void Server::readyRead() {
    // Handle incoming data from connected clients
    QTcpSocket *senderSocket = qobject_cast<QTcpSocket *>(sender());

    while (senderSocket->bytesAvailable() > 0) {
        QByteArray data = senderSocket->readAll();
        QString dataString = QString::fromUtf8(data);

        // Process the received data as needed
        std::cout << "Received data: " << dataString.toStdString() << std::endl;
    }
}

void Server::disconnected() {
    // Remove disconnected clients
    QTcpSocket *senderSocket = qobject_cast<QTcpSocket *>(sender());
    clients.removeOne(senderSocket);

    qDebug() << "Client disconnected: " << senderSocket->socketDescriptor();
    senderSocket->deleteLater();
}

void Server::sendToAllClients(const QByteArray &data) {
    for (QTcpSocket *client : clients) {
        client->write(data);
        client->flush();
    }
}
