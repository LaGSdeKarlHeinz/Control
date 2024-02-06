/**
    @authors M.Rochat & E.Dutruy (Co-TL GS 23-24)
    @date 06-02-2024
    @brief Client side of data stream handling
*/

#include "ClientManager.h"
#include <json/json.h>
#include <iostream>

void ClientManager::subscribe(const std::string& field, CallbackFunction callback) {
    subscriptions[field].append(callback);
}

void ClientManager::handleReceivedData(const QString& data) {
    // Handle the received data and call the subscribed callbacks
    
        

    Json::Value root; 
    JSONCPP_STRING err;
    const auto rawJsonLength = static_cast<int>(data.toStdString().length());

    // Parse the data received
    Json::CharReaderBuilder builder;
    const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    if (!reader->parse(data.toStdString().c_str(), data.toStdString().c_str() + rawJsonLength, &root,
                        &err)) {
        std::cout << "error" << std::endl;
        return;
    }
    
    // get all fields received
    for (Json::Value member: root.getMemberNames()) {
        // get the callbacks associated to this fields 
        const QVector<CallbackFunction>& callbacks = subscriptions.value(member.asString());
        // call them004
        
        for (const auto& callback : callbacks) {
            callback(root[member.asString()].asString());
        }
    }
        
    

}
