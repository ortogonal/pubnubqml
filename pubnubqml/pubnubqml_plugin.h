#ifndef PUBNUBQML_PLUGIN_H
#define PUBNUBQML_PLUGIN_H

#include <QQmlExtensionPlugin>

class PubNubQmlPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri);
};

#endif // PUBNUBQML_PLUGIN_H

