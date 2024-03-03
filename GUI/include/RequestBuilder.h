#ifndef REQUESTBUILDER_H
#define REQUESTBUILDER_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>

enum class RequestType {
    POST,
    GET,
    INTERNAL,
    SUBSCRIBE,
    UNSUBSCRIBE
};

class RequestBuilder : public QObject
{
    Q_OBJECT
public:
    explicit RequestBuilder(QObject *parent = nullptr);
    
    RequestBuilder& setHeader(RequestType type);
    RequestBuilder& addField(const QString& key, const QString& value);
    RequestBuilder& addField(const QString& key, int value);
    RequestBuilder& addField(const QString& key, const QJsonObject& value);
    
    QJsonObject build() const;
    QString toString() const;
    
private:
    RequestType m_headerType;
    QJsonObject m_payload;
};

#endif // REQUESTBUILDER_H