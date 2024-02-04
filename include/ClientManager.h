#ifndef CLIENTIMPLEMENTATION_H
#define CLIENTIMPLEMENTATION_H

#include "ClientInterface.h"
#include <QMap>
#include <QVector>
#include <string>

class ClientManager: public ClientInterface {
public:
    void subscribe(const std::string& field, CallbackFunction callback) override;
    void handleReceivedData(const QString& data) override;
    
    // Additional functions as needed

private:
    QMap<std::string, QVector<CallbackFunction>> subscriptions;
};

#endif // CLIENTIMPLEMENTATION_H
