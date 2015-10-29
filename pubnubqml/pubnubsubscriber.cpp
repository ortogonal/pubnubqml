#include "pubnubsubscriber.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

PubNubSubscriberPrivate::PubNubSubscriberPrivate(PubNubSubscriber *parent)
    : m_parent(parent)
{
}

void PubNubSubscriberPrivate::outcome(pubnub_res result) {
    if (result == PNR_OK && m_parent && m_parent->m_subscriber) {
        QString msg;
        QString channel;
        do {
            msg = m_parent->m_subscriber->get();
            channel = m_parent->m_subscriber->get_channel();

            if (msg.length() > 0) {
                if (!m_parent->m_raw) {
                    QJsonDocument doc = QJsonDocument::fromJson(msg.toUtf8());
                    msg = doc.object().value("message").toString();
                }

                emit m_parent->message(channel, msg);
            }
        } while (msg != QString());

        m_parent->subscribe();
    }
}

PubNubSubscriber::PubNubSubscriber(QQuickItem *parent)
    : QQuickItem(parent)
    , m_subscribeKey(QString())
    , m_channels(QString())
    , m_subscriber(NULL)
    , m_d(new PubNubSubscriberPrivate(this))
{
}

PubNubSubscriber::~PubNubSubscriber() {
    if (m_d)
        delete m_d;
}

QString PubNubSubscriber::subscribeKey() const {
    return m_subscribeKey;
}

QString PubNubSubscriber::channels() const {
    return m_channels;
}

bool PubNubSubscriber::raw() const {
    return m_raw;
}

void PubNubSubscriber::setSubscribeKey(QString key) {
    if (m_subscribeKey != key) {
        m_subscribeKey = key;

        if (m_subscriber) {
            m_subscriber->deleteLater();
        }

        m_subscriber = new pubnub_qt(QString(), m_subscribeKey);
        m_subscriber->set_uuid("qt_qml");
        connect(m_subscriber, SIGNAL(outcome(pubnub_res)),
                m_d, SLOT(outcome(pubnub_res)));

        if (m_channels.length() > 0) {
            subscribe();
        }

        emit subscribeKeyChanged();
    }
}

void PubNubSubscriber::setChannels(QString channels) {
    if (m_channels != channels) {
        m_channels = channels;

        if (m_subscriber) {
            subscribe();
        }

        emit channelsChanged();
    }
}

void PubNubSubscriber::setRaw(bool raw) {
    if (m_raw != raw) {
        m_raw = raw;
        emit rawChanged();
    }
}

void PubNubSubscriber::subscribe() {
    if (!m_subscriber)
        return;

    QStringList l;
    foreach(QString s, m_channels.split(",")) {
        l << s.trimmed();
    }

    m_subscriber->cancel();
    pubnub_res result = m_subscriber->subscribe("chat");
    if (result != PNR_STARTED)
        qDebug() << Q_FUNC_INFO << "Failed";
}
