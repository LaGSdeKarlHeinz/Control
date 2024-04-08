#include <iostream>

#include "RequestHandler.h"
#include <QJsonDocument>
#include <QJsonObject>

RequestHandler::RequestHandler(QObject *parent) : QObject(parent) {}

void RequestHandler::handleRequest(const QString &request, QTcpSocket* senderSocket)
{
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(request.toUtf8(), &error);
    if (error.error != QJsonParseError::NoError) {
        std::cout << "Error parsing JSON: " << error.errorString().toStdString() << std::endl;
        
    }
    QJsonObject json = doc.object();

    QString header = json["header"].toString();

    // Emit the corresponding signal based on the header type
    if (header == "subscribe")
        emit subscribe(json, senderSocket);
    else if (header == "unsubscribe") 
        emit unsubscribe(json, senderSocket);
    else if (header == "get")
        emit get(json, senderSocket);
    else if (header == "post")
        emit post(json, senderSocket);
    else 
        std::cout << "Unknown header type: " << header.toStdString() << std::endl;
    // Add more conditions for other types if needed
}
