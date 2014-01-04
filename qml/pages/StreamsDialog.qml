import QtQuick 2.0
import Sailfish.Silica 1.0

import "../components"

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

    DialogHeader {
        id: header
        acceptText: selectedQuality + ", " + selectedFormat
        dialog: dialog
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
    }

    Label {
        id: infoLabel
        anchors {
            top: header.bottom
            horizontalCenter: parent.horizontalCenter
        }
        width: parent.width - 2 * Theme.paddingLarge
        height: implicitHeight
        text: "Select quality/format for current channel"
        horizontalAlignment: Text.AlignLeft
        font.pixelSize: Theme.fontSizeSmall
    }

    SilicaListView {
        id: listView
        anchors {
            top: infoLabel.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right
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
        var qualities = _channelsModel.streamsQualities();
        var formats = _channelsModel.streamsFormats();

        var newStreams = new Array()
        var quality, format
        for (var key in streams) {
            quality = key.replace(/\d+/g, '')
            format = streams[key]
            if (quality in newStreams)
                newStreams[quality].push(format)
            else
                newStreams[quality] = new Array(format)
        }

        for (var q = 0; q < qualities.length; ++q) {
            for (var f = 0; f < formats.length; ++f) {
                quality = qualities[q]
                format = formats[f]
                if ((quality in newStreams) && (newStreams[quality].indexOf(format) !== -1))
                    listModel.append({"quality": quality, "format": format})
            }
        }
    }

    function defineSelected() {
        currentQuality = _player.streamQualityText();
        currentFormat = _player.streamFormatText();
        selectedQuality = currentQuality
        selectedFormat = currentFormat
    }

    function changeStreams() {
        if (selectedQuality != currentQuality || selectedFormat != currentFormat)
            _player.changeStream(selectedQuality, selectedFormat)
    }

    onAccepted: changeStreams()

    Connections {
        target: controlPanel
        onClose: close()
    }

    Component.onCompleted: {
        defineSelected()
        fillStreamsList()
    }
}
