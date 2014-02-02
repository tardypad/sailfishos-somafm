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

DockedPanel {
    id: songPanel

    property alias _title: titleLabel.text
    property alias _artist: artistLabel.text
    property alias _album: albumLabel.text
    property alias _date: dateLabel.text
    property int _minHeight: titleLabel.height + artistLabel.height + dateLabel.height
                            + 2*Theme.paddingLarge + 2*Theme.paddingMedium
    property bool _hasAlbum: _album !== ""

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
                    width: 80
                    font {
                        italic: true
                        pixelSize: Theme.fontSizeExtraSmall
                    }
                    color: Theme.secondaryColor
                    horizontalAlignment: Text.AlignRight
                }
                Label {
                    id: artistLabel
                    font.pixelSize: Theme.fontSizeSmall
                    anchors.baseline: artistHeaderLabel.baseline
                }
            }
            Row {
                spacing: Theme.paddingLarge
                Label {
                    id: titleHeaderLabel
                    text: "Title"
                    width: 80
                    font {
                        italic: true
                        pixelSize: Theme.fontSizeExtraSmall
                    }
                    color: Theme.secondaryColor
                    horizontalAlignment: Text.AlignRight
                }
                Label {
                    id: titleLabel
                    font.pixelSize: Theme.fontSizeSmall
                    anchors.baseline: titleHeaderLabel.baseline
                }
            }
            Row {
                spacing: Theme.paddingLarge
                visible: _hasAlbum
                Label {
                    id: albumHeaderLabel
                    text: "Album"
                    width: 80
                    font {
                        italic: true
                        pixelSize: Theme.fontSizeExtraSmall
                    }
                    color: Theme.secondaryColor
                    horizontalAlignment: Text.AlignRight
                }
                Label {
                    id: albumLabel
                    font.pixelSize: Theme.fontSizeSmall
                    anchors.baseline: albumHeaderLabel.baseline
                }
            }
            Row {
                spacing: Theme.paddingLarge
                Label {
                    id: dateHeaderLabel
                    text: "Added"
                    width: 80
                    font {
                        italic: true
                        pixelSize: Theme.fontSizeExtraSmall
                    }
                    color: Theme.secondaryColor
                    horizontalAlignment: Text.AlignRight
                }
                Label {
                    id: dateLabel
                    font.pixelSize: Theme.fontSizeSmall
                    anchors.baseline: dateHeaderLabel.baseline
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
