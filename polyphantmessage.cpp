#include "polyphantmessage.h"

PolyphantMessage::PolyphantMessage(const QJsonObject json)
{
    _type = json["type"].toString();
    _payload = json["payload"].toObject();
    _meta = json["meta"].toObject();
}

PolyphantMessage::PolyphantMessage(const QString type, const QJsonValue payload, int requestId, const QJsonObject meta) :
    _type(type),
    _payload(payload),
    _meta(meta)
{
    _requestId = requestId;
}

void PolyphantMessage::setPayload(const QJsonValue &payload)
{
    _payload = payload;
}

void PolyphantMessage::setResponseSuccess(bool success)
{
    _type += success ? "_SUCCESS" : "_ERROR";
}

const QJsonObject PolyphantMessage::toJson() const {
    QJsonObject o({
                      { "type", _type }
                  });

    if (!_payload.isNull())
        o["payload"] = _payload;

    if (_requestId > 0)
        _meta["requestId"] = _requestId;

    if (!_meta.isEmpty())
        o["meta"] = _meta;

    return o;
}

PolyphantMessage* PolyphantMessage::makeResponse() const
{
    QJsonObject meta({
                         { "commType", "response" },
                     });

    return new PolyphantMessage(_type, QJsonObject(), _meta["requestId"].toInt(), meta);
}
