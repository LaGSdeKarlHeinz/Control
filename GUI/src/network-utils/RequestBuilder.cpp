#include "RequestBuilder.h"
#include <QJsonDocument>

RequestBuilder::RequestBuilder(QObject *parent)
    : QObject(parent), m_headerType(RequestType::POST) {}

RequestBuilder& RequestBuilder::setHeader(RequestType type) {
    m_headerType = type;
    return *this;
}

RequestBuilder& RequestBuilder::addField(const QString& key, const QString& value) {
    m_payload[key] = value;
    return *this;
}

RequestBuilder &RequestBuilder::addField(const QString &key, int value)
{
    m_payload[key] = value;
    return *this;
}

RequestBuilder& RequestBuilder::addField(const QString& key, const QJsonObject& value) {
    m_payload[key] = value;
    return *this;
}

QJsonObject RequestBuilder::build() const {
    QJsonObject request;
    switch (m_headerType) {
        case RequestType::POST:
            request["header"] = "post";
            break;
        case RequestType::GET:
            request["header"] = "get";
            break;
        case RequestType::INTERNAL:
            request["header"] = "internal";
            break;
        case RequestType::SUBSCRIBE:
            request["header"] = "subscribe";
            break;
        case RequestType::UNSUBSCRIBE:
            request["header"] = "unsubscribe";
            break;
    }
    request["payload"] = m_payload;
    return request;
}

QString RequestBuilder::toString() const {
    return QString(QJsonDocument(build()).toJson());
}