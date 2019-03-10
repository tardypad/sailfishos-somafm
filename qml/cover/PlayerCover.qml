/**
 * Copyright (c) 2013-2019 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

import QtQuick 2.0
import Sailfish.Silica 1.0

import "../components"

MainCover {
    property bool _isPlaying: control.state === "playing"
    property bool _isSongBookmark: control.isSongBookmark
    property url _channelImageMediumUrl: control.channelImageMediumUrl
    property string _artist: control.artist
    property string _title: control.title

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
        CoverInfo {
            id: coverInfo
            artist: _artist
            title: _title
            isBookmark: _isSongBookmark
            isPlaying: _isPlaying
        }
    ]

    CoverActionList {
        id: coverActionPlaying
        iconBackground: true
        enabled: _isPlaying

        CoverAction {
            iconSource: somaTheme.getIconSource("pause", "cover")
            onTriggered: control.pause()
        }
        CoverAction {
            iconSource: _isSongBookmark ? somaTheme.getIconSource("unbookmark", "cover") : somaTheme.getIconSource("bookmark", "cover")
            onTriggered: {
                if (_isSongBookmark)
                    control.removeSongFromBookmarks()
                else
                    control.addSongToBookmarks()
            }
        }
    }

    CoverActionList {
        id: coverActionPause
        iconBackground: true
        enabled: !_isPlaying

        CoverAction {
            iconSource: somaTheme.getIconSource("play", "cover")
            onTriggered: control.play()
        }
    }

    function showBookmarkInfo() {
        if (status !== Cover.Active) return;

        coverInfo.showBookmark()
    }

    Connections {
        target: _bookmarksManager
        onBookmarkAdded: showBookmarkInfo()
        onBookmarkRemoved: showBookmarkInfo()
    }

}

