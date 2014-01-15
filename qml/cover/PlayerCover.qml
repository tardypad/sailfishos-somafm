import QtQuick 2.0
import Sailfish.Silica 1.0

MainCover {
    property bool isPlaying: controlPanel.isPlaying
    property bool isSongBookmark: controlPanel.isSongBookmark
    property alias channelImageUrl: channelImage.source

    content: Image {
        id: channelImage
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        verticalAlignment:Image.AlignTop
        horizontalAlignment: Image.AlignLeft
        smooth: true
        clip: true
    }

    CoverActionList {
        id: coverAction
        iconBackground: true

        CoverAction {
            iconSource: isPlaying ? "image://theme/icon-cover-pause" : "image://theme/icon-cover-play"
            onTriggered: {
                if (isPlaying)
                    controlPanel.pause()
                else
                    controlPanel.play()
            }
        }
        CoverAction {
            iconSource: isSongBookmark ? somaTheme.getIconUrl("cover-un-bookmark") : somaTheme.getIconUrl("cover-bookmark")
            onTriggered: {
                if (isSongBookmark)
                    controlPanel.removeSongFromBookmarks()
                else
                    controlPanel.addSongToBookmarks()
            }
        }
    }

    Component.onCompleted: {
        channelImageUrl = _player.channelImageMediumUrl()
        isPlaying = _player.isPlaying()
    }

    Connections {
        target: _player
        onChannelChanged: channelImageUrl = _player.channelImageMediumUrl()
        onPlayStarted: isPlaying = true
        onPauseStarted: isPlaying = false
    }
}

