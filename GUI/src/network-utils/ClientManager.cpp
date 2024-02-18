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
#include "RequestBuilder.h"
#include "../Setup.h"


ClientManager::ClientManager(QObject *parent) : ClientInterface(parent) {
    
    socket = new QTcpSocket(this);
    
    
    connect(socket, &QTcpSocket::connected, this, &ClientManager::connected);
    connect(socket, &QTcpSocket::readyRead, this, &ClientManager::readyRead);
    connect(socket, &QTcpSocket::disconnected, this, &ClientManager::disconnected);

    socket->connectToHost(network::serverIP, network::serverPort);
    if (!socket->waitForConnected(3000)) {
        std::cout << "Error: " << socket->errorString().toStdString() << std::endl;
    }
  
    
    
}


void ClientManager::readyRead() {
        // Handle incoming data from the server
        QByteArray data = socket->readAll();
        std::cout << "Received data: " << data.toStdString() << std::endl;
        handleReceivedData(QString::fromUtf8(data));
    }


void ClientManager::subscribe(const std::string& field, CallbackFunction<QString> callback) {
    if (subscriptionsStrings[field].size() == 0) 
        sendSubscribeRequest(QString::fromStdString(field));
    subscriptionsStrings[field].append(callback);
    
}

void ClientManager::sendSubscribeRequest(const QString& field) {
    
    RequestBuilder builder;
    builder.setHeader(RequestType::SUBSCRIBE);
    builder.addField("field", field);
    // socket->waitForReadyRead();
    socket->write(builder.toString().toUtf8());
    
    socket->flush();
    socket->waitForBytesWritten();
    
}

void ClientManager::subscribe(const std::string& field, CallbackFunction<QJsonValue> callback) {
    if (subscriptionsJson[field].size() == 0) 
        sendSubscribeRequest(QString::fromStdString(field));
    subscriptionsJson[field].append(callback);
    
}


void ClientManager::handleReceivedData(const QString& data) {
    notifyChildrenFields(jsonFromString(data));
}

QJsonObject ClientManager::jsonFromString(const QString& data) {
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8(), &error);
    if (error.error != QJsonParseError::NoError) {
        std::cout << "Error parsing JSON: " << error.errorString().toStdString() << std::endl;
        return QJsonObject();
    }
    return doc.object();
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
    QJsonObject json = jsonFromString(data);
    if (json.value("header") == "internal") {
        std::cout << "internal" << std::endl;
        handleReceivedData(data);
    } else {
        QString con = QString(R"({
            "header": "subscribe",
            "payload":{
                "field": "data"
            }
        })");
        socket->write(con.toUtf8());
        socket->waitForBytesWritten();
        QString con2 = QString(R"({
            "header": "unsubscribe",
            "payload":{
                "field": "data"
            }
        })");
        socket->write(con2.toUtf8());
        socket->flush();
    }
    
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