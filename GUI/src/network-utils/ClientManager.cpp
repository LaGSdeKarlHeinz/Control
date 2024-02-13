/**
    @authors M.Rochat & E.Dutruy (Co-TL GS 23-24)
    @date 06-02-2024
    @brief Client side of data stream handling
*/
#include <iostream>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QDebug>
#include <QtNetwork/QTcpSocket>
#include <QObject>
#include<unistd.h> 

#include "ClientManager.h"
#include "../Setup.h"


ClientManager::ClientManager(QObject *parent) : ClientInterface(parent) {
    
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::connected, this, &ClientManager::connected);
    connect(socket, &QTcpSocket::readyRead, this, &ClientManager::readyRead);
    connect(socket, &QTcpSocket::disconnected, this, &ClientManager::disconnected);
    std::cout << "Connecting to server" << std::endl;
    socket->connectToHost(network::serverIP, network::serverPort);
    std::cout << "Connected" << std::endl;
    
}

void ClientManager::subscribe(const std::string& field, CallbackFunction<QString> callback) {
    subscriptionsStrings[field].append(callback);
}

void ClientManager::subscribe(const std::string& field, CallbackFunction<QJsonValue> callback) {
    subscriptionsJson[field].append(callback);
}


void ClientManager::handleReceivedData(const QString& data) {
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8(), &error);
    if (error.error != QJsonParseError::NoError) {
        std::cout << "Error parsing JSON: " << error.errorString().toStdString() << std::endl;
        return;
    }

    notifyChildrenFields(doc.object());
}



void ClientManager::notifyChildrenFields(const QJsonObject& localObject) {
    for (auto it = localObject.constBegin(); it != localObject.constEnd(); ++it) {
       
        const QVector<CallbackFunction<QString>>& callbacksStrings = subscriptionsStrings.value(it.key().toStdString());
        const QVector<CallbackFunction<QJsonValue>>& callbacksJson = subscriptionsJson.value(it.key().toStdString());

        const QJsonValue& value = it.value();
        for (const auto& callback: callbacksJson) {
            callback(value);
        }
        
        

        if (value.isObject()) {
            notifyChildrenFields(value.toObject());
        } else if (value.isArray()) {
            const QJsonArray array = value.toArray();
            for (const QJsonValue& element : array) {
                if (element.isObject()) {
                    notifyChildrenFields(element.toObject());
                } 
            }
        } else {

            for (const auto& callback : callbacksStrings) {
                callback(value.toVariant().toString());     
            }
        }
    }
}

void ClientManager::send(const QString& data) {
    // send command "serialNameUsed", "serialStatus" 
    handleReceivedData(QString(R"({
        "AV": {
            "serialNameUsed": "-",
            "serialStatus" : "close",
            "dataField": "data",
           
            "togglebutton1": "unknown"
            }
        })"));
    sleep(3);
    if (p) {
        handleReceivedData(QString(R"({
        "AV": {
            "serialNameUsed": "-",
            "serialStatus" : "close",
            "dataField": "data",
            "togglebutton1": "open"
            }
        }
    )"));
    } else {
        handleReceivedData(QString(R"({
        "AV": {
            "serialNameUsed": "-",
            "serialStatus" : "open",
            "dataField": "data",
           "togglebutton1": "close"
            }
        }
    )"));
    }
    p = !p;
    
}