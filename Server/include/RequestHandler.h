#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include <QObject>
#include <QString>
#include <QtNetwork/QTcpSocket>

class RequestHandler : public QObject
{
    Q_OBJECT
public:
    explicit RequestHandler(QObject *parent = nullptr);

public slots:
    void handleRequest(const QString &request,  QTcpSocket *senderSocket);

signals:
    void subscribe(const QJsonObject &request,  QTcpSocket *senderSocket);
    void unsubscribe(const QJsonObject &request,  QTcpSocket *senderSocket);
    void get(const QJsonObject &request,  QTcpSocket *senderSocket);
    void post(const QJsonObject &request,  QTcpSocket *senderSocket);
};

#endif // REQUESTHANDLER_H
