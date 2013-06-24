import QtQuick 1.1
import Sailfish.Silica 1.0

Item {
    id: newsDelegate
    x: theme.paddingLarge
    width: parent.width - 2*theme.paddingLarge
    height: childrenRect.height + theme.paddingLarge

    Label {
        id: dateLabel
        text: Qt.formatDateTime(date, 'MMM, d')
        font {
            pixelSize: theme.fontSizeExtraSmall
            italic: true
        }
        color: theme.secondaryColor
        anchors {
            left: parent.left
            top: parent.top
        }
    }

    Label {
        id: contentLabel
        text: content
        font.pixelSize: theme.fontSizeExtraSmall
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignJustify
        anchors {
            top: dateLabel.bottom
            left: parent.left
            right: parent.right
        }
    }
}
