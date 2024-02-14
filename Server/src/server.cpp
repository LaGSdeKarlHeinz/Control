#include "Server.h"
#include <iostream>
#include "ClientManager.h"
#include <string>
#include <QJsonDocument>


#include "../Capsule/src/capsule.h"
#include "../ERT_RF_Protocol_Interface/PacketDefinition.h"



Server::Server(QObject *parent) : QTcpServer(parent), requestHandler(this), serialPort(new QSerialPort(this)), capsule(&Server::handleSerialPacket, this) {
    
    connect(&requestHandler, &RequestHandler::subscribe, this, &Server::receiveSubscribe);
    connect(&requestHandler, &RequestHandler::unsubscribe, this, &Server::receiveUnsubscribe);
    connect(&requestHandler, &RequestHandler::get, this, &Server::receiveGet);
    connect(&requestHandler, &RequestHandler::post, this, &Server::receivePost);
    connect(serialPort, &QSerialPort::readyRead, this, &Server::receiveSerialData);
    connect(serialPort, &QSerialPort::errorOccurred, this, &Server::serialError);

    openSerialPort();
}



void Server::openSerialPort() {
    int ctr = 0;
    QString serial_port_name = "";
    if (!serialPort->isOpen()) {
        do {
            serial_port_name = "ttyACM" + QString::number(ctr++);
            serialPort->setPortName(serial_port_name);
        } while (!serialPort->open(QIODevice::ReadWrite) && ctr <= 50);
        if (!serialPort->isOpen()) { // opening on WSL => ttyS
            ctr = 0;
            do {
                serial_port_name = "ttyS" + QString::number(ctr++);
                serialPort->setPortName(serial_port_name);
            } while (!serialPort->open(QIODevice::ReadWrite) && ctr <= 50);
        }
        if (serialPort->isOpen()) {
            std::cout << "Serial port open" << std::endl;
        } else {
            std::cout << "Impossible to find valid serialPort port" << std::endl;
        }
    }

}

void Server::receiveSerialData() {
    QByteArray data = serialPort->readAll();
    for (auto &&item: data) {
        capsule.decode(item);
    }
}

void Server::serialError() {
    std::cout << "Serial port error: " << serialPort->errorString().toStdString() << std::endl;
}

void Server::incomingConnection(qintptr socketDescriptor) {
    // A new connection is incoming
    QTcpSocket *client = new QTcpSocket(this);
    client->setSocketDescriptor(socketDescriptor);

    connect(client, &QTcpSocket::readyRead, this, &Server::readyRead);
    connect(client, &QTcpSocket::disconnected, this, &Server::disconnected);

    clients.append(client);

    std::cout << "Client connected: " << socketDescriptor << std::endl;
}

void Server::receiveSubscribe(const QJsonObject &request,  QTcpSocket *senderSocket) {
    // Handle the subscribe request
    QString field = request.value("payload").toObject().value("field").toString();
    std::cout << "socket: " << senderSocket << std::endl;
    subscriptionMap["data"].append(senderSocket);
    std::cout << "Subscribed to: " << field.toStdString() << std::endl; 
}

void Server::receiveUnsubscribe(const QJsonObject &request,  QTcpSocket *senderSocket) {
    // Handle the unsubscribe request
    QString field = request.value("payload").toObject().value("field").toString();
    subscriptionMap[field].removeOne(senderSocket);
    std::cout << "Unsubscribed from: " << subscriptionMap[field].size() << std::endl;
}

void Server::receiveGet(const QJsonObject &request,  QTcpSocket *senderSocket) {
    // Handle the get request
    std::cout << "Received get request" << std::endl;
    QString field = request["field"].toString();
    QByteArray data = "Data for " + field.toUtf8();
    sendToAllClients(data);
}

void Server::receivePost(const QJsonObject &request,  QTcpSocket *senderSocket) {
    // Handle the post request
    std::cout << "Received post request" << std::endl;
    QString field = request["field"].toString();
    QString value = request["value"].toString();
    QByteArray data = "Data for " + field.toUtf8() + " updated to " + value.toUtf8();
    sendToAllClients(data);
}

void Server::readyRead() {
    // Handle incoming data from connected clients
    QTcpSocket *senderSocket = qobject_cast<QTcpSocket *>(sender());

    while (senderSocket->bytesAvailable() > 0) {
        QByteArray data = senderSocket->readAll();
        QString dataString = QString::fromUtf8(data);
        requestHandler.handleRequest(dataString, senderSocket);
        // Process the received data as needed
        std::cout << "Received data: " << dataString.toStdString() << std::endl;
        QString d = QString(R"(
        {
            "header": "post",
            "payload": {
                "%1": "new data from server"
            }
        }
    )").arg("data");
        
        for (QTcpSocket *subscribedSocket : subscriptionMap["data"]) {
         
            subscribedSocket->write(d.toUtf8());
        }
        
    }
}



void Server::disconnected() {
    // Remove disconnected clients
    QTcpSocket *senderSocket = qobject_cast<QTcpSocket *>(sender());
    clients.removeOne(senderSocket);

    qDebug() << "Client disconnected: " << senderSocket->socketDescriptor();
    senderSocket->deleteLater();
}

void Server::sendToAllClients(const QByteArray &data) {
    for (QTcpSocket *client : clients) {
        client->write(data);
        client->flush();
    }
}


void Server::updateSubscriptions(const QJsonObject &newData) {
    
    for (QTcpSocket *subscribedSocket : subscriptionMap["data"]) {
        QJsonDocument doc(newData);
        subscribedSocket->write(QString(QJsonDocument(newData).toJson()).toUtf8());
        subscribedSocket->flush();
    }
}

void Server::handleSerialPacket(uint8_t packetId, uint8_t *dataIn, uint32_t len) {
    //    packet_ctr++;
    static int altitude_max = 0;
    static int altitude_max_r = 0;
    av_downlink_t data;
    memccpy(&data, dataIn, len, sizeof(av_downlink_t));
 
    // std::cout << "Packet received, ID: " << +packetId << " len: "  << len << std::endl;
    switch (packetId) {
        case 0x00: 
            std::cout << "Packet with ID 00 received : " << +packetId << std::endl;
            break;
        case CAPSULE_ID::AV_TELEMETRY: {
            
             // Create a JSON object
            QJsonObject jsonObj;

            // Iterate over struct members and add them to the JSON object
            jsonObj["packet_nbr"] = static_cast<int>(data.packet_nbr);
            jsonObj["timestamp"] = static_cast<int>(data.timestamp);
            jsonObj["gnss_lon"] = static_cast<double>(data.gnss_lon);
            jsonObj["gnss_lat"] = static_cast<double>(data.gnss_lat);
            jsonObj["gnss_alt"] = static_cast<double>(data.gnss_alt);
            jsonObj["gnss_lon_r"] = static_cast<double>(data.gnss_lon_r);
            jsonObj["gnss_lat_r"] = static_cast<double>(data.gnss_lat_r);
            jsonObj["gnss_alt_r"] = static_cast<double>(data.gnss_alt_r);
            jsonObj["gnss_vertical_speed"] = static_cast<double>(data.gnss_vertical_speed);
            jsonObj["N2_pressure"] = static_cast<double>(data.N2_pressure);
            jsonObj["fuel_pressure"] = static_cast<double>(data.fuel_pressure);
            jsonObj["LOX_pressure"] = static_cast<double>(data.LOX_pressure);
            jsonObj["fuel_level"] = static_cast<double>(data.fuel_level);
            jsonObj["LOX_level"] = static_cast<double>(data.LOX_level);
            jsonObj["engine_temp"] = static_cast<double>(data.engine_temp);
            jsonObj["igniter_pressure"] = static_cast<double>(data.igniter_pressure);
            jsonObj["LOX_inj_pressure"] = static_cast<double>(data.LOX_inj_pressure);
            jsonObj["fuel_inj_pressure"] = static_cast<double>(data.fuel_inj_pressure);
            jsonObj["chamber_pressure"] = static_cast<double>(data.chamber_pressure);

            // Create a sub-object for engine_state_t
            QJsonObject engineStateObj;
            engineStateObj["igniter_LOX"] = static_cast<int>(data.engine_state.igniter_LOX);
            engineStateObj["igniter_fuel"] = static_cast<int>(data.engine_state.igniter_fuel);
            engineStateObj["main_LOX"] = static_cast<int>(data.engine_state.main_LOX);
            engineStateObj["main_fuel"] = static_cast<int>(data.engine_state.main_fuel);
            engineStateObj["vent_LOX"] = static_cast<int>(data.engine_state.vent_LOX);
            engineStateObj["vent_fuel"] = static_cast<int>(data.engine_state.vent_fuel);

            // Add the sub-object to the main JSON object
            jsonObj["engine_state"] = engineStateObj;
            updateSubscriptions(jsonObj);
            break;
        }
        case CAPSULE_ID::GSE_TELEMETRY: {
            
            

            break;
        }
        default:
            break;
    }
        
}
