import QtQuick 2.0
import Sailfish.Silica 1.0

MainCover {
    property bool isPlaying: controlPanel.state === "playing"
    property bool isSongBookmark: controlPanel.isSongBookmark
    property url channelImageMediumUrl: controlPanel.channelImageMediumUrl

    content: Image {
        id: channelImage
        anchors.fill: parent
        source: channelImageMediumUrl
        fillMode: Image.PreserveAspectCrop
        verticalAlignment:Image.AlignTop
        horizontalAlignment: Image.AlignLeft
        smooth: true
        clip: true
    }

    CoverActionList {
        id: coverActionPlaying
        iconBackground: true
        enabled: isPlaying

        CoverAction {
            iconSource: "image://theme/icon-cover-pause"
            onTriggered: controlPanel.pause()
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

    CoverActionList {
        id: coverActionPause
        iconBackground: true
        enabled: !isPlaying

        CoverAction {
            iconSource: "image://theme/icon-cover-play"
            onTriggered: controlPanel.play()
        }
    }
}

