#ifndef PUBNUB_H
#define PUBNUB_H

#include <QQuickItem>
#include "pubnubsubscriber.h"
#include <pubnub_qt.h>

class PubNubPublisher;
class PubNubPublisherPrivate : public QObject {
    Q_OBJECT
public:
    PubNubPublisherPrivate(PubNubPublisher* parent);
public slots:
    void outcome(pubnub_res result);
private:
    PubNubPublisher* m_parent;
};

class PubNubPublisher : public PubNubSubscriber
{
    Q_OBJECT
    Q_DISABLE_COPY(PubNubPublisher)
    Q_PROPERTY(QString publishKey READ publishKey WRITE setPublishKey NOTIFY publishKeyChanged)

public:
    PubNubPublisher(QQuickItem *parent = 0);
    ~PubNubPublisher();

    Q_INVOKABLE void publish(QString channel, QString message);

    QString publishKey() const;

public slots:
    void setPublishKey(QString key);

signals:
    void publishKeyChanged();
    void publishResult();

protected:
    QString m_publishKey;
    pubnub_qt* m_publisher;

    PubNubPublisherPrivate* m_dpub;

    friend class PubNubPublisherPrivate;
};

#endif // PUBNUB_H

