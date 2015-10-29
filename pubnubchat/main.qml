import QtQuick 2.3
import QtQuick.Window 2.2
import com.combitech.pubnub 1.0

Window {
    visible: true
    width: 300
    height: 400

    PubNubSubscriber {
        subscribeKey: "<Your sub-key, sign up at pubnub.com>"
        channels: "chat"
        onMessage: {
            msgModel.append({message: message})
        }
    }

    PubNubPublisher {
        id: pub
        publishKey: "<Your pub-key, sign up at pubnub.com>"
        subscribeKey: "<Your sub-key, sign up at pubnub.com>"

        onPublishResult: {
            console.log("Publish result")
        }
    }

    Rectangle {
        id: rec
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: 28
        border.width: 2

        TextInput {
            id: msg
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: 50
            anchors.margins: 2
            font.pixelSize: 10
        }
        Rectangle {
            anchors.left: msg.right
            anchors.top: rec.top
            anchors.right: rec.right
            anchors.bottom: rec.bottom
            color: "green"
            Text {
                anchors.centerIn: parent
                text: "Send"
                color: "white"
                font.pixelSize: 10
            }
            MouseArea {
                anchors.fill: parent
                onClicked: pub.publish("chat", msg.text)
            }
        }
    }

    ListModel {
        id: msgModel
        ListElement { message: "Start chat" }
    }

    ListView {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: rec.top

        model: msgModel
        delegate: Text {
            height: 20
            text: message
            font.pixelSize: 12
        }
    }

}

