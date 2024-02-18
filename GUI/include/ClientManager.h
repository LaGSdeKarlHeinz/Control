/**
    @authors M.Rochat & E.Dutruy (Co-TL GS 23-24)
    @date 06-02-2024
    @brief Client side of data stream handling
*/

#ifndef CLIENTIMPLEMENTATION_H
#define CLIENTIMPLEMENTATION_H

#include <iostream>
#include <string>

#include <QMap>
#include <QVector>
#include <QJsonObject>
#include <QtNetwork/QTcpSocket>




#include "ClientInterface.h"

class ClientManager: public ClientInterface {
    Q_OBJECT
public:

    ClientManager(QObject *parent = nullptr);

    void subscribe(const std::string& field, CallbackFunction<QString> callback) override;
    void subscribe(const std::string& field, CallbackFunction<QJsonValue> callback) override;
    void handleReceivedData(const QString& data) override;
    void send(const QString& data) override;
    void sendSubscribeRequest(const QString& field);
    

private slots:
    void connected() {
        std::cout << "Connected to server" << std::endl;
    }

    void readyRead();

    void disconnected() {
         std::cout << "Disconnected from the server" << std::endl;
    }


private:
    QMap<std::string, QVector<CallbackFunction<QString>>> subscriptionsStrings;
    QMap<std::string, QVector<CallbackFunction<QJsonValue>>> subscriptionsJson;

    bool p = false;
    QTcpSocket *socket;
    
    QJsonObject jsonFromString(const QString& data);
    // void notifyChildrenFields(Json::Value local_root); const QJsonObject& localObject
    void notifyChildrenFields(const QJsonObject& localObject);
};

#endif // CLIENTIMPLEMENTATION_H
