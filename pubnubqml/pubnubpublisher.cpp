#include "pubnubpublisher.h"
#include <QJsonDocument>
#include <QJsonObject>

PubNubPublisherPrivate::PubNubPublisherPrivate(PubNubPublisher *parent)
    : m_parent(parent) {
}

void PubNubPublisherPrivate::outcome(pubnub_res result) {
    qDebug() << Q_FUNC_INFO;
}

PubNubPublisher::PubNubPublisher(QQuickItem *parent)
    : PubNubSubscriber(parent)
    , m_publishKey(QString())
    , m_publisher(NULL)
    , m_dpub(new PubNubPublisherPrivate(this))
{
}

PubNubPublisher::~PubNubPublisher()
{
    if (m_publisher)
        m_publisher->deleteLater();
}

void PubNubPublisher::publish(QString channel, QString message) {
    if (m_publisher) {
        if (!m_raw) {
            QJsonDocument doc;
            QJsonObject obj;
            obj.insert("message", message);
            doc.setObject(obj);
            message = QString(doc.toJson());
        }
        pubnub_res result = m_publisher->publish(channel, message);
        if (result != PNR_STARTED)
            qDebug() << Q_FUNC_INFO << "Failed";
    }
}

QString PubNubPublisher::publishKey() const {
    return m_publishKey;
}

void PubNubPublisher::setPublishKey(QString key) {
    if (m_publishKey != key) {
        m_publishKey = key;

        if (m_publisher) {
            m_publisher->deleteLater();
        }
        m_publisher = new pubnub_qt(m_publishKey, m_subscribeKey);
        connect((QObject*)m_publisher, SIGNAL(outcome(pubnub_res)),
                (QObject*)m_dpub, SLOT(outcome(pubnub_res)));
        emit publishKeyChanged();
    }
}
