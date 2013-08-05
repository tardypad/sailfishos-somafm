import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: newsDelegate
    x: Theme.paddingLarge
    width: parent.width - 2*Theme.paddingLarge
    height: childrenRect.height + Theme.paddingLarge

    Label {
        id: dateLabel
        text: Qt.formatDateTime(date, 'MMM, d')
        font {
            pixelSize: Theme.fontSizeExtraSmall
            italic: true
        }
        color: Theme.secondaryColor
        anchors {
            left: parent.left
            top: parent.top
        }
    }

    Label {
        id: contentLabel
        text: content
        font.pixelSize: Theme.fontSizeExtraSmall
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignJustify
        anchors {
            top: dateLabel.bottom
            left: parent.left
            right: parent.right
        }
    }
}
