#include "Server.h"

Server::Server(QObject *parent) : QTcpServer(parent) {
}

void Server::incomingConnection(qintptr socketDescriptor) {
    // A new connection is incoming
    QTcpSocket *client = new QTcpSocket(this);
    client->setSocketDescriptor(socketDescriptor);

    connect(client, &QTcpSocket::readyRead, this, &Server::readyRead);
    connect(client, &QTcpSocket::disconnected, this, &Server::disconnected);

    clients.append(client);

    qDebug() << "Client connected: " << socketDescriptor;
}


void Server::readyRead() {
    // Handle incoming data from connected clients
    QTcpSocket *senderSocket = qobject_cast<QTcpSocket *>(sender());

    while (senderSocket->bytesAvailable() > 0) {
        QByteArray data = senderSocket->readAll();
        // Process the received data as needed
        qDebug() << "Received data: " << data;
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