/**
 *
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 **/


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

