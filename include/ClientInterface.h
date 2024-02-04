#ifndef CLIENTINTERFACE_H
#define CLIENTINTERFACE_H

#include <functional>
#include <QString>

class ClientInterface {
public:
    virtual ~ClientInterface() = default;

    using CallbackFunction = std::function<void(const std::string&)>;

    virtual void subscribe(const std::string& field, CallbackFunction callback) = 0;
    virtual void handleReceivedData(const QString& data) = 0;
};

#endif // CLIENTINTERFACE_H
