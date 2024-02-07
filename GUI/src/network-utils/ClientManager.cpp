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

#include "ClientManager.h"




void ClientManager::subscribe(const std::string& field, CallbackFunction callback) {
    subscriptions[field].append(callback);
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
       
        const QVector<CallbackFunction>& callbacks = subscriptions.value(it.key().toStdString());

        const QJsonValue& value = it.value();
        if (value.isObject()) {
            notifyChildrenFields(value.toObject());
        } else if (value.isArray()) {
            const QJsonArray array = value.toArray();
            for (const QJsonValue& element : array) {
                if (element.isObject()) {
                    notifyChildrenFields(element.toObject());
                } else {
                    std::cout << element.toVariant().toString().toStdString() << std::endl;
                }
            }
        } else {

            for (const auto& callback : callbacks) {
                callback(value.toVariant().toString());     
            }
        }
    }
}