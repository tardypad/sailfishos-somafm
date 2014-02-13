/**
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

import QtQuick 2.0
import Sailfish.Silica 1.0

DockedPanel {
    id: songPanel

    property alias _title: titleLabel.text
    property alias _artist: artistLabel.text
    property alias _album: albumLabel.text
    property alias _date: dateLabel.text
    property int _minHeight: titleLabel.height + artistLabel.height + dateLabel.height
                            + 2*Theme.paddingLarge + 2*Theme.paddingMedium
    property bool _hasAlbum: _album !== ""

    property int _headerWidth: 80
    property int _textWidth: width - _headerWidth - Theme.paddingLarge

    width: parent.width
    height: _hasAlbum ? _minHeight + albumLabel.height + Theme.paddingMedium : _minHeight
    dock: Dock.Bottom
    opacity: 0

    MouseArea {
        anchors.fill: parent
        onClicked: hide()
    }

    Rectangle {
        anchors.fill: parent
        color: Theme.rgba(Theme.secondaryHighlightColor, 0.9)

        Column {
            spacing: Theme.paddingMedium
            anchors {
                top: parent.top
                topMargin: Theme.paddingLarge
            }

            Row {
                spacing: Theme.paddingLarge
                Label {
                    id: artistHeaderLabel
                    text: "Artist"
                    width: _headerWidth
                    font {
                        italic: true
                        pixelSize: Theme.fontSizeExtraSmall
                    }
                    color: Theme.secondaryColor
                    horizontalAlignment: Text.AlignRight
                }
                Label {
                    id: artistLabel
                    width:_textWidth
                    font.pixelSize: Theme.fontSizeSmall
                    anchors.baseline: artistHeaderLabel.baseline
                    truncationMode: TruncationMode.Fade
                }
            }
            Row {
                spacing: Theme.paddingLarge
                Label {
                    id: titleHeaderLabel
                    text: "Title"
                    width: _headerWidth
                    font {
                        italic: true
                        pixelSize: Theme.fontSizeExtraSmall
                    }
                    color: Theme.secondaryColor
                    horizontalAlignment: Text.AlignRight
                }
                Label {
                    id: titleLabel
                    width:_textWidth
                    font.pixelSize: Theme.fontSizeSmall
                    anchors.baseline: titleHeaderLabel.baseline
                    truncationMode: TruncationMode.Fade
                }
            }
            Row {
                spacing: Theme.paddingLarge
                visible: _hasAlbum
                Label {
                    id: albumHeaderLabel
                    text: "Album"
                    width: _headerWidth
                    font {
                        italic: true
                        pixelSize: Theme.fontSizeExtraSmall
                    }
                    color: Theme.secondaryColor
                    horizontalAlignment: Text.AlignRight
                }
                Label {
                    id: albumLabel
                    width:_textWidth
                    font.pixelSize: Theme.fontSizeSmall
                    anchors.baseline: albumHeaderLabel.baseline
                    truncationMode: TruncationMode.Fade
                }
            }
            Row {
                spacing: Theme.paddingLarge
                Label {
                    id: dateHeaderLabel
                    text: "Added"
                    width: _headerWidth
                    font {
                        italic: true
                        pixelSize: Theme.fontSizeExtraSmall
                    }
                    color: Theme.secondaryColor
                    horizontalAlignment: Text.AlignRight
                }
                Label {
                    id: dateLabel
                    width:_textWidth
                    font.pixelSize: Theme.fontSizeSmall
                    anchors.baseline: dateHeaderLabel.baseline
                    truncationMode: TruncationMode.Fade
                }
            }
        }
    }

    Connections {
        target: songPanel
        onMovingChanged: {
            if (!moving && !open) {
                opacity = 0
            }
        }
    }

    function showBookmark(artist, title, album, date) {
        opacity = 1
        _title = title
        _artist = artist
        _album = album
        _date = Qt.formatDateTime(date, 'ddd dd MMM, hh:mm')
        show()
    }

    function isBookmarkDisplayed(artist, title) {
        return _artist === artist && _title === title
    }
}
