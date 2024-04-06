#include "Server.h"
#include <iostream>
#include "ClientManager.h"
#include <string>
#include <QJsonDocument>
#include <QMap>
#include <QString>
#include <QJsonObject>


#include "../Capsule/src/capsule.h"
#include "../ERT_RF_Protocol_Interface/PacketDefinition.h"
#include "RequestAdapter.h"



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
    serialPort->setBaudRate(QSerialPort::Baud115200);
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
    int field = request.value("payload").toObject().value("field").toInt();

    std::cout << "socket: " << senderSocket << std::endl;
    if (subscriptionMap[field].contains(senderSocket)) {
        std::cout << "Already subscribed to: " << QString::number(field).toStdString() << std::endl;
        return;
    }
    subscriptionMap[field].append(senderSocket);
    std::cout << "Subscribed to: " << QString::number(field).toStdString() << std::endl; 
}

void Server::receiveUnsubscribe(const QJsonObject &request,  QTcpSocket *senderSocket) {
    // Handle the unsubscribe request
    int field = request.value("payload").toObject().value("field").toInt();
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
    QJsonDocument doc(request);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    if (request["payload"].toObject().contains("cmd")) {
        handleCommand(request);
        /*
        int f = request["payload"].toObject()["cmd"].toInt();
        int order = request["payload"].toObject()["cmd_order"].toInt();
        std::cout << "cmd: " << f << " order: " << order << std::endl;
        av_uplink_t p = createUplinkPacketFromRequest((GUI_FIELD)f, order);
        sendSerialPacket(CAPSULE_ID::GS_CMD, (uint8_t*) &p, av_uplink_size);
        */
    }
    std::cout << strJson.toStdString() << std::endl;
}

void Server::readyRead() {
    // Handle incoming data from connected clients
    QTcpSocket *senderSocket = qobject_cast<QTcpSocket *>(sender());

    while (senderSocket->bytesAvailable() > 0) {
        QByteArray data = senderSocket->readAll();
        QString dataString = QString::fromUtf8(data);
        QString jsonString(dataString);

        // Split the string by '}{'
        QStringList jsonStrings = jsonString.split("}{");
        for (const QString &jsonStr : jsonStrings) {
        
            requestHandler.handleRequest(jsonStr, senderSocket);
            
        }

    }
}


void Server::disconnected() {
    // Remove disconnected clients
    QTcpSocket *senderSocket = qobject_cast<QTcpSocket *>(sender());
    clients.removeOne(senderSocket);
    foreach(const int &key, subscriptionMap.keys()) {
        QList<QTcpSocket *> &socketList = subscriptionMap[key];
        socketList.removeOne(senderSocket);
    }
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
    

    for (auto it = newData.constBegin(); it != newData.constEnd(); ++it) {
        QRegularExpression regex("^-?\\d+$"); // Regular expression to match integers, including negative ones
        QRegularExpressionMatch match = regex.match(it.key());
        const QList<QTcpSocket *> sockets = subscriptionMap.value(it.key().toInt());  

        const QJsonValue& value = it.value();
        RequestBuilder rBuilder;
        rBuilder.setHeader(RequestType::POST); 

        if (value.isObject()) {
            updateSubscriptions(value.toObject());
            for (QTcpSocket *socket: sockets) {
                std::cout << "Sending data to client" << std::endl;
                rBuilder.addField(it.key(), QString(QJsonDocument(value.toObject()).toJson()));
                QByteArray data = rBuilder.toString().toUtf8();
                socket->write(data, data.size());
                socket->waitForBytesWritten();
                socket->flush();
                
            }
        } else if (value.isArray()) {
            const QJsonArray array = value.toArray();
            for (const QJsonValue& element : array) {
                if (element.isObject()) {
                    updateSubscriptions(element.toObject());
                } 
            }
        } else {
            for (QTcpSocket *socket: sockets) {
                std::cout << "Sending data to client" << std::endl;
                rBuilder.addField(it.key(), value.toString());
                QByteArray data = rBuilder.toString().toUtf8();
                socket->write(data, data.size());
                socket->waitForBytesWritten();
                socket->flush();
                
                
                
            }
        }
    }


}

void Server::handleCommand(const QJsonObject &command) {
    // Handle the command
    int f = command["payload"].toObject()["cmd"].toInt();
    RequestBuilder b = RequestBuilder();
    switch (f)
    {

    case GUI_FIELD::GUI_CMD_SET_SERIAL_STATUS:
        if (command["payload"].toObject()["cmd_order"].toString() == "close") {
            if (serialPort->isOpen()) {
                serialPort->close();
            }
        } else {
            openSerialPort();
        }
    case GUI_FIELD::SERIAL_STATUS:
        std::cout << "Serial status" << std::endl;
        b.setHeader(RequestType::POST);
        b.addField(QString::number(GUI_FIELD::SERIAL_STATUS), serialPort->isOpen() ? "open" : "close");
        std::cout << b.toString().toStdString() << std::endl;
        updateSubscriptions(b.build());
        break;
    

    case GUI_FIELD::SERIAL_NAME_USE:
        b.setHeader(RequestType::POST);
        b.addField(QString::number(GUI_FIELD::SERIAL_NAME_USE), serialPort->portName());
        updateSubscriptions(b.build());
        break;

        

    default:
        int order = command["payload"].toObject()["cmd_order"].toInt();
        std::cout << "cmd: " << f << " order: " << order << std::endl;
        av_uplink_t p = createUplinkPacketFromRequest((GUI_FIELD)f, order);
        sendSerialPacket(CAPSULE_ID::GS_CMD, (uint8_t*) &p, av_uplink_size);
        break;
    }
    
}

void Server::sendSerialPacket(uint8_t packetId, uint8_t *packet, uint32_t size) {
    uint8_t *packetToSend = capsule.encode(packetId, packet, size);
    serialPort->write((char *) packetToSend,capsule.getCodedLen(size));
    delete[] packetToSend;
    std::cout << "Packet sent to radio Board" << std::endl;
}



void Server::handleSerialPacket(uint8_t packetId, uint8_t *dataIn, uint32_t len) {
    //    packet_ctr++;
    static int altitude_max = 0;
    static int altitude_max_r = 0;
    av_downlink_t dataAv;
    PacketGSE_downlink dataGse;
    switch (packetId) {
        case 0x00: 
            std::cout << "Packet with ID 00 received : " << +packetId << std::endl;
            break;
        case CAPSULE_ID::AV_TELEMETRY: {
            
             // Create a JSON object
            QJsonObject jsonObj;
            
            // Iterate over struct members and add them to the JSON object
            jsonObj[QString::number(GUI_FIELD::PACKET_NBR)] = static_cast<int>(dataAv.packet_nbr);
            jsonObj[QString::number(GUI_FIELD::TIMESTAMP)] = static_cast<int>(dataAv.timestamp);
            jsonObj[QString::number(GUI_FIELD::GNSS_LON)] = static_cast<double>(dataAv.gnss_lon);
            jsonObj[QString::number(GUI_FIELD::GNSS_LAT)] = static_cast<double>(dataAv.gnss_lat);
            jsonObj[QString::number(GUI_FIELD::GNSS_ALT)] = static_cast<double>(dataAv.gnss_alt);
            jsonObj[QString::number(GUI_FIELD::GNSS_LON_R)] = static_cast<double>(dataAv.gnss_lon_r);
            jsonObj[QString::number(GUI_FIELD::GNSS_LAT_R)] = static_cast<double>(dataAv.gnss_lat_r);
            jsonObj[QString::number(GUI_FIELD::GNSS_ALT_R)] = static_cast<double>(dataAv.gnss_alt_r);
            jsonObj[QString::number(GUI_FIELD::GNSS_VERTICAL_SPEED)] = static_cast<double>(dataAv.gnss_vertical_speed);
            jsonObj[QString::number(GUI_FIELD::N2_PRESSURE)] = static_cast<double>(dataAv.N2_pressure);
            jsonObj[QString::number(GUI_FIELD::FUEL_PRESSURE)] = static_cast<double>(dataAv.fuel_pressure);
            jsonObj[QString::number(GUI_FIELD::LOX_PRESSURE)] = static_cast<double>(dataAv.LOX_pressure);
            jsonObj[QString::number(GUI_FIELD::FUEL_LEVEL)] = static_cast<double>(dataAv.fuel_level);
            jsonObj[QString::number(GUI_FIELD::LOX_LEVEL)] = static_cast<double>(dataAv.LOX_level);
            jsonObj[QString::number(GUI_FIELD::ENGINE_TEMP)] = static_cast<double>(dataAv.engine_temp);
            jsonObj[QString::number(GUI_FIELD::IGNITER_PRESSURE)] = static_cast<double>(dataAv.igniter_pressure);
            jsonObj[QString::number(GUI_FIELD::LOX_INJ_PRESSURE)] = static_cast<double>(dataAv.LOX_inj_pressure);
            jsonObj[QString::number(GUI_FIELD::FUEL_INJ_PRESSURE)] = static_cast<double>(dataAv.fuel_inj_pressure);
            jsonObj[QString::number(GUI_FIELD::CHAMBER_PRESSURE)] = static_cast<double>(dataAv.chamber_pressure);

            // Create a sub-object for engine_state_t
            QJsonObject engineStateObj;
            engineStateObj[QString::number(GUI_FIELD::IGNITER_LOX)] = static_cast<int>(dataAv.engine_state.igniter_LOX);
            engineStateObj[QString::number(GUI_FIELD::IGNITER_FUEL)] = static_cast<int>(dataAv.engine_state.igniter_fuel);
            engineStateObj[QString::number(GUI_FIELD::MAIN_LOX)] = static_cast<int>(dataAv.engine_state.main_LOX);
            engineStateObj[QString::number(GUI_FIELD::MAIN_FUEL)] = static_cast<int>(dataAv.engine_state.main_fuel);
            engineStateObj[QString::number(GUI_FIELD::VENT_LOX)] = static_cast<int>(dataAv.engine_state.vent_LOX);
            engineStateObj[QString::number(GUI_FIELD::VENT_FUEL)] = static_cast<int>(dataAv.engine_state.vent_fuel);

            // Add the sub-object to the main JSON object
            jsonObj[QString::number(GUI_FIELD::ENGINE_STATE)] = engineStateObj;
            updateSubscriptions(jsonObj);
            break;
        }
        case CAPSULE_ID::GSE_TELEMETRY: {
            // Create a JSON object
            QJsonObject jsonObj;

            // Add primitive data members to JSON object
            jsonObj[QString::number(GUI_FIELD::TANK_PRESSURE)] = static_cast<double>(dataGse.tankPressure);
            jsonObj[QString::number(GUI_FIELD::TANK_TEMPERATURE)] = static_cast<double>(dataGse.tankTemperature);
            jsonObj[QString::number(GUI_FIELD::FILLING_PRESSURE)] = static_cast<double>(dataGse.fillingPressure);
            jsonObj[QString::number(GUI_FIELD::DISCONNECT_ACTIVE)] = dataGse.disconnectActive;
            jsonObj[QString::number(GUI_FIELD::LOADCELL_RAW)] = static_cast<int>(dataGse.loadcellRaw);

            // Create a sub-object for status
            QJsonObject statusObj;
            statusObj[QString::number(GUI_FIELD::FILLINGN2O)] = static_cast<int>(dataGse.status.fillingN2O);
            statusObj[QString::number(GUI_FIELD::GSE_VENT)] = static_cast<int>(dataGse.status.vent);

            // Add the sub-object to the main JSON object
            jsonObj[QString::number(GUI_FIELD::GSE_CMD_STATUS)] = statusObj;

            updateSubscriptions(jsonObj);
            break;
        }
        default:
            break;
    }        
}




void Server::simulateJsonData() {
    // Create a JSON object
    QJsonObject jsonObj;

    // Add primitive data members to JSON object
    jsonObj[QString::number(GUI_FIELD::AV_STATE)] = "1000";
    jsonObj[QString::number(GUI_FIELD::PACKET_NBR)] = "25";
    jsonObj[QString::number(GUI_FIELD::DOWNRANGE)] = "1013";
    jsonObj["1234"] = 50;

    // Create a sub-object for location
    QJsonObject locationObj;
    locationObj["4532"] = 45.5;
    locationObj["1123"] = 9.2;

    // Add the sub-object to the main JSON object
    jsonObj["53252"] = locationObj;


    // Convert the JSON object to a string
    QString jsonString = QString(QJsonDocument(jsonObj).toJson());

    // Send the JSON string to all connected clients
    std::cout << "Fake data sent" << std::endl;

    updateSubscriptions(jsonObj);
}