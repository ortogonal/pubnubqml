# pubnubqml

PubNubQml is a simple extenstion plugin for Qt5.

PubNubQml uses the PubNub service to publish and subscribe to different channels. To use it you need to have an acount at PubNub. Sign up at http://pubnub.com.

## How to use it
PubNubQml is really simple to use.

### Example subscriber in Qml
```
import QtQuick 2.3
import QtQuick.Window 2.2
import com.combitech.pubnub 1.0

Window {
    visible: true

    PubNubSubscriber {
        subscribeKey: "<Your sub-key here!>"
        channels: "chat"
        onMessage: {
            console.log("A new message", message)
        }
    }
}
```

### Example publisher in Qml
```
import QtQuick 2.3
import QtQuick.Window 2.2
import com.combitech.pubnub 1.0

Window {
    visible: true

    PubNubPublisher {
        id: pub
        publishKey: "<Your pub-key here!>"
        subscribeKey: "<Your sub-key here!>"
    }
    
    MouseArea {
      anchors.fill: parent
      // Argument 1 is the channel.
      // Argument 2 is the message.
      onClicked: pub.publish("chat", "Hello Qt/QML & PubNub")
    }
}
```
