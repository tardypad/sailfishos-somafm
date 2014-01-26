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
