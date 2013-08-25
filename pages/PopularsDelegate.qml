import QtQuick 2.0
import Sailfish.Silica 1.0

ChannelsDelegate {
    Label {
        id: channelListenersLabel
        text: listeners
        anchors {
            right: listenerIcon.left
            rightMargin: Theme.paddingSmall
            verticalCenter: listenerIcon.verticalCenter
        }
        color: Theme.secondaryColor
        font {
            pixelSize: Theme.fontSizeExtraSmall * 0.8;
            italic: true
        }
    }

    Image {
        id: listenerIcon
        source: "qrc:/icon/listener"
        smooth: true
        height: Theme.iconSizeSmall * 0.75
        width: Theme.iconSizeSmall * 0.75
        anchors {
            top: parent.top
            topMargin: Theme.paddingSmall
            right: parent.right
            rightMargin: Theme.paddingSmall
        }
        fillMode: Image.PreserveAspectFit
    }
}
