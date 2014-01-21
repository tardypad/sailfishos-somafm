import QtQuick 2.0
import Sailfish.Silica 1.0

MainCover {
    property bool isPlaying: controlPanel.state === "playing"
    property bool isSongBookmark: controlPanel.isSongBookmark
    property url channelImageMediumUrl: controlPanel.channelImageMediumUrl
    property string artist: controlPanel.artist
    property string title: controlPanel.title

    content: [
        Image {
            id: channelImage
            anchors.fill: parent
            source: channelImageMediumUrl
            fillMode: Image.PreserveAspectCrop
            verticalAlignment:Image.AlignTop
            horizontalAlignment: Image.AlignLeft
            smooth: true
            clip: true
        },
        Loader {
            id: bookmarkLoader
            anchors.fill: parent
        }
    ]

    CoverActionList {
        id: coverActionPlaying
        iconBackground: true
        enabled: isPlaying

        CoverAction {
            iconSource: somaTheme.getIconUrl("pause", "cover")
            onTriggered: controlPanel.pause()
        }
        CoverAction {
            iconSource: isSongBookmark ? somaTheme.getIconUrl("unbookmark", "cover") : somaTheme.getIconUrl("bookmark", "cover")
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
            iconSource: somaTheme.getIconUrl("play", "cover")
            onTriggered: controlPanel.play()
        }
    }

    function showBookmarkInfo() {
        if (status !== Cover.Active) return;

        if (bookmarkLoader.status === Loader.Null)
            bookmarkLoader.source = Qt.resolvedUrl("../components/BookmarkCoverInfo.qml")

        bookmarkLoader.item.show(artist, title, isSongBookmark)
    }

    Connections {
        target: _bookmarksManager
        onBookmarkAdded: showBookmarkInfo()
        onBookmarkRemoved: showBookmarkInfo()
    }
}

