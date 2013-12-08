import QtQuick 2.0
import Sailfish.Silica 1.0

import "components"

Dialog {
    id: dialog
    objectName: "StreamDialog"

    property string channelId
    property string selectedQuality
    property string selectedFormat
    property string currentQuality
    property string currentFormat
    property color selectedColor: Theme.rgba(Theme.highlightBackgroundColor, Theme.highlightBackgroundOpacity)
    property color currentColor: Theme.rgba(Theme.highlightBackgroundColor, Theme.highlightBackgroundOpacity / 3)

    SilicaListView {
        id: listView
        anchors.fill: parent
        header: DialogHeader {
            acceptText: selectedQuality + ", " + selectedFormat
            dialog: dialog
        }
        footer: Label {
            text: "Better quality requires better connection"
            anchors {
                left: parent.left
                leftMargin: Theme.paddingLarge
                right: parent.right
                rightMargin: Theme.paddingLarge
            }
            font {
                italic: true
                pixelSize: Theme.fontSizeExtraSmall
            }
            horizontalAlignment: Text.AlignRight
            height: implicitHeight
        }
        model: ListModel {
            id: listModel
        }
        section {
            property: 'quality'
            delegate: SectionHeader {
                text: section + " quality"
            }
        }
        delegate: BackgroundItem {
            property bool selected: quality === selectedQuality && format === selectedFormat
            property bool current: quality === currentQuality && format === currentFormat
            height: Theme.itemSizeSmall
            highlighted: down || selected || current
            highlightedColor: selected || down ? selectedColor : currentColor
            Label {
                text: format + " format"
                anchors.centerIn: parent
            }
            onClicked: {
                selectedQuality = quality
                selectedFormat = format
            }
        }
    }

    function fillStreamsList() {
        var streams = _channelsModel.channelStreams(channelId)
        var quality, format
        for (var key in streams) {
            quality = key.replace(/\d+/g, '')
            format = streams[key]
            listModel.append({"quality": quality, "format": format})
        }
    }

    function defineSelected() {
        currentQuality = _player.streamQualityText();
        currentFormat = _player.streamFormatText();
        selectedQuality = currentQuality
        selectedFormat = currentFormat
    }

    Component.onCompleted: {
        defineSelected()
        fillStreamsList()
    }
}
