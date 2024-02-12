/**
    @authors M.Rochat & E.Dutruy (Co-TL GS 23-24)
    @date 06-02-2024
    @brief Interface between app and server
*/

#ifndef CLIENTINTERFACE_H
#define CLIENTINTERFACE_H

#include <functional>
#include <QString>

class ClientInterface {
public:
    virtual ~ClientInterface() = default;

    template<typename T>
    using CallbackFunction= std::function<void(const T&)>;
    // using CallbackFunction = std::function<void(const QString)>;
    
    virtual void subscribe(const std::string& field, CallbackFunction<QString> callback) = 0;
    virtual void subscribe(const std::string& field, CallbackFunction<QJsonValue> callback) = 0;
    virtual void handleReceivedData(const QString& data) = 0;
    virtual void send(const QString& data) = 0;
};

#endif // CLIENTINTERFACE_H
