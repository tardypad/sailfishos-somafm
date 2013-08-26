import QtQuick 2.0
import Sailfish.Silica 1.0

DockedPanel {
    id: songPanel

    property int index
    property alias title: titleLabel.text
    property alias artist: artistLabel.text
    property alias album: albumLabel.text
    property alias date: dateLabel.text

    width: parent.width
    height: 2*Theme.itemSizeMedium + 2*Theme.paddingLarge
    dock: Dock.Bottom

    MouseArea {
        anchors.fill: parent
        onClicked: songPanel.hide()
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
}
