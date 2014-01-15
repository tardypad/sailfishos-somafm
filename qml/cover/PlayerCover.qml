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
}

