import QtQuick 2.0
import Sailfish.Silica 1.0

MainCover {
    property bool _isPlaying: controlPanel.state === "playing"
    property bool _isSongBookmark: controlPanel.isSongBookmark
    property url _channelImageMediumUrl: controlPanel.channelImageMediumUrl
    property string _artist: controlPanel.artist
    property string _title: controlPanel.title

    content: [
        Image {
            id: channelImage
            anchors.fill: parent
            source: _channelImageMediumUrl
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
        enabled: _isPlaying

        CoverAction {
            iconSource: somaTheme.getIconSource("pause", "cover")
            onTriggered: controlPanel.pause()
        }
        CoverAction {
            iconSource: _isSongBookmark ? somaTheme.getIconSource("unbookmark", "cover") : somaTheme.getIconSource("bookmark", "cover")
            onTriggered: {
                if (_isSongBookmark)
                    controlPanel.removeSongFromBookmarks()
                else
                    controlPanel.addSongToBookmarks()
            }
        }
    }

    CoverActionList {
        id: coverActionPause
        iconBackground: true
        enabled: !_isPlaying

        CoverAction {
            iconSource: somaTheme.getIconSource("play", "cover")
            onTriggered: controlPanel.play()
        }
    }

    function showBookmarkInfo() {
        if (status !== Cover.Active) return;

        if (bookmarkLoader.status === Loader.Null)
            bookmarkLoader.source = Qt.resolvedUrl("../components/BookmarkCoverInfo.qml")

        bookmarkLoader.item.show(_artist, _title, _isSongBookmark)
    }

    Connections {
        target: _bookmarksManager
        onBookmarkAdded: showBookmarkInfo()
        onBookmarkRemoved: showBookmarkInfo()
    }
}

