#pragma once

#include <QObject>
#include <QtCore/QLoggingCategory>
#include <QNdefMessage>

Q_DECLARE_LOGGING_CATEGORY(NfcLog)

class QUrl;
class QPixmap;
class QNearFieldManager;
class QNearFieldTarget;
class QNearFieldTarget;

class Nfc : public QObject
{
    Q_OBJECT
public:
    explicit Nfc(QObject *parent = 0);


signals:
    void annotatedUrl(const QUrl &url, const QString &title, const QPixmap &pixmap);

public slots:
    void targetDetected(QNearFieldTarget *target);
    void targetLost(QNearFieldTarget *target);
    void handlePolledNdefMessage(QNdefMessage message);
    void handleMessage(QNdefMessage message, QNearFieldTarget *target);
private:
    QNearFieldManager *manager;
};
