#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtSerialPort/QSerialPort>
#include <QMap>


#include "RequestHandler.h"
#include "../Capsule/src/capsule.h"
#include "../../GUI/include/RequestBuilder.h"

class Server : public QTcpServer {
    Q_OBJECT

public:
    Server(QObject *parent = nullptr);
    void sendToAllClients(const QByteArray &data);
    void handleSerialPacket(uint8_t packetId, uint8_t *dataIn, uint32_t len);
    void simulateJsonData();
    
protected:
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    void readyRead();
    void disconnected();

private:

    void receiveSubscribe(const QJsonObject &request,  QTcpSocket *senderSocket);
    void receiveUnsubscribe(const QJsonObject &request,  QTcpSocket *senderSocket);
    void receivePost(const QJsonObject &request,  QTcpSocket *senderSocket);
    void receiveGet(const QJsonObject &request,  QTcpSocket *senderSocket);
    void receiveSerialData();
    void serialError();
    void openSerialPort();
    void updateSubscriptions(const QJsonObject &newData);


    

    QMap<int, QList<QTcpSocket *>> subscriptionMap;
    QList<QTcpSocket *> clients;

    
    QSerialPort *serialPort;
    RequestHandler requestHandler;
    Capsule<Server> capsule;
};

#endif /* SERVER_H */
