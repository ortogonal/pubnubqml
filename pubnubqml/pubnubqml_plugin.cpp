#include "pubnubqml_plugin.h"
#include "pubnubpublisher.h"

#include <qqml.h>

void PubNubQmlPlugin::registerTypes(const char *uri)
{
    // @uri com.combitech.pubnub
    qmlRegisterType<PubNubSubscriber>(uri, 1, 0, "PubNubSubscriber");
    qmlRegisterType<PubNubPublisher>(uri, 1, 0, "PubNubPublisher");
}


