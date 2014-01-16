import QtQuick 2.0
import Sailfish.Silica 1.0

Rectangle {
    id: info

    property alias artist: artistLabel.text
    property alias title: titleLabel.text

    anchors.fill: parent
    color: Theme.rgba(Theme.highlightBackgroundColor, 0.9)
    opacity: 0

    Column {
        anchors {
            top: parent.top
            topMargin: Theme.paddingLarge
            horizontalCenter: parent.horizontalCenter
        }
        width: parent.width - 2*Theme.paddingMedium

        Label {
            id: artistLabel
            width: parent.width
            truncationMode: TruncationMode.Fade
            font.pixelSize: Theme.fontSizeSmall
            horizontalAlignment: implicitWidth < width ? Text.AlignHCenter : Text.AlignLeft
        }

        Label {
            id: titleLabel
            width: parent.width
            truncationMode: TruncationMode.Fade
            font {
                pixelSize: Theme.fontSizeSmall
                italic: true
            }
            horizontalAlignment: implicitWidth < width ? Text.AlignHCenter : Text.AlignLeft
        }
    }

    function show(artist, title) {
        info.artist = artist
        info.title = title
        opacity = 1
        displayTimer.start()
    }

    function hide() {
        opacity = 0
    }

    Timer {
        id: displayTimer
        interval: 3000
        onTriggered: hide()
    }

    Behavior on opacity {
        NumberAnimation { }
    }
}
