/**
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

import QtQuick 2.0
import Sailfish.Silica 1.0

Rectangle {
    id: info

    property alias artist: artistLabel.text
    property alias title: titleLabel.text
    property bool isPlaying
    property bool isBookmark

    property bool _isSongCoverDisplayed: _settings.songCover()
    property bool _isShowingBookmark: false

    anchors.fill: parent
    color: Theme.rgba(Theme.highlightBackgroundColor, 0.9)
    opacity: isPlaying && (_isSongCoverDisplayed || _isShowingBookmark) ? 1 : 0

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
            text: isBookmark ? "added" : "removed"
            opacity: _isShowingBookmark ? 1 : 0

            Behavior on opacity {
                NumberAnimation { }
            }
        }
    }

    function showBookmark() {
        _isShowingBookmark = true
        displayTimer.start()
    }

    function hide() {        
        _isShowingBookmark = false
    }

    Timer {
        id: displayTimer
        interval: 3000
        onTriggered: hide()
    }

    Behavior on opacity {
        NumberAnimation { }
    }

    Connections {
        target: _settings
        onSongCoverChanged: _isSongCoverDisplayed = _settings.songCover()
    }
}
