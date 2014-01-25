import QtQuick 2.0
import Sailfish.Silica 1.0

Rectangle {
    id: info

    property alias _artist: artistLabel.text
    property alias _title: titleLabel.text
    property bool _isBookmark

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

        Label {
            id: infoLabel
            width: parent.width
            font.pixelSize: Theme.fontSizeSmall
            horizontalAlignment: Text.AlignHCenter
            text: _isBookmark ? "added" : "removed"
        }
    }

    function show(artist, title, isBookmark) {
        _artist = artist
        _title = title
        _isBookmark = isBookmark
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
