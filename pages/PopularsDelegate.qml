import QtQuick 1.1
import Sailfish.Silica 1.0

ChannelsDelegate {
    Label {
        id: channelListenersLabel
        text: listeners
        anchors {
            right: listenerIcon.left
            rightMargin: theme.paddingSmall
            verticalCenter: listenerIcon.verticalCenter
        }
        color: theme.secondaryColor
        font {
            pixelSize: theme.fontSizeExtraSmall * 0.8;
            italic: true
        }
    }

    Image {
        id: listenerIcon
        source: "qrc:/icons/listener"
        smooth: true
        height: parent.height / 5
        width: parent.height / 5
        anchors {
            top: parent.top
            topMargin: theme.paddingSmall
            right: parent.right
            rightMargin: theme.paddingSmall
        }
        fillMode: Image.PreserveAspectFit
    }
}
