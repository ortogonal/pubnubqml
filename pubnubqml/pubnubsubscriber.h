#ifndef PUBNUBSUBSCRIBER_H
#define PUBNUBSUBSCRIBER_H

#include <QQuickItem>
#include <pubnub_qt.h>

class PubNubSubscriber;
class PubNubSubscriberPrivate : public QObject {
    Q_OBJECT
public:
    PubNubSubscriberPrivate(PubNubSubscriber* parent);
public slots:
    void outcome(pubnub_res result);
private:
    PubNubSubscriber* m_parent;
};

class PubNubSubscriber : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(PubNubSubscriber)
    Q_PROPERTY(QString subscribeKey READ subscribeKey WRITE setSubscribeKey NOTIFY subscribeKeyChanged)
    Q_PROPERTY(QString channels READ channels WRITE setChannels NOTIFY channelsChanged)
    Q_PROPERTY(bool raw READ raw WRITE setRaw NOTIFY rawChanged)

public:
    PubNubSubscriber(QQuickItem *parent = 0);
    virtual ~PubNubSubscriber();

    QString subscribeKey() const;
    QString channels() const;
    bool raw() const;

public slots:
    void setSubscribeKey(QString key);
    void setChannels(QString channels);
    void setRaw(bool raw);

signals:
    void subscribeKeyChanged();
    void channelsChanged();
    void rawChanged();

    void message(QString channel, QString message);

protected:
    QString m_subscribeKey;
    QString m_channels;

    pubnub_qt* m_subscriber;
    bool m_raw;

private:
    void subscribe();
    PubNubSubscriberPrivate* m_d;
    friend class PubNubSubscriberPrivate;
};

#endif // PUBNUBSUBSCRIBER_H
