#pragma once

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QtCore/QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(ConnmanLog)

class ConnmanPrivate;
class NetworkService;

class Connman : public QObject
{
    Q_OBJECT
public:
    explicit Connman(QObject *parent = 0);
    void start();
    bool connectToWifi(const QString &wifiId, const QString &passphrase);
    bool disconnectFromWifi(const QString &wifiId);

signals:
    void availableWifisUpdated(const QJsonArray &list);
    void wifiChanged(const QJsonObject &wifi, const QString &state);
    void goneOnline();

private slots:
    void iterateServices();
    void connectToKnownWifi();
    void agentPassphraseRequested(const QString &servicePath, const QVariantMap &fields);
    void enableWifi();
    void checkState();

private:
    ConnmanPrivate *d_ptr;
    Q_DECLARE_PRIVATE(Connman);
    QString kalamiIdForService(const NetworkService *service);
};
