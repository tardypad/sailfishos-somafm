import QtQuick 2.0
import Sailfish.Silica 1.0

CoverBackground {
    property bool isPlaying
    property alias channelImageUrl: channelImage.source

    Image {
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
                    _player.pause()
                else
                    _player.play()
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

