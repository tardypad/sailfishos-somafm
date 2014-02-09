/**
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

import QtQuick 2.0
import Sailfish.Silica 1.0

import "../components"

Dialog {
    id: dialog
    objectName: "StreamDialog"

    property string channelId

    property string _selectedQuality
    property string _selectedFormat
    property string _currentQuality
    property string _currentFormat
    property color _selectedColor: Theme.rgba(Theme.highlightBackgroundColor, Theme.highlightBackgroundOpacity)
    property color _currentColor: Theme.rgba(Theme.highlightBackgroundColor, Theme.highlightBackgroundOpacity / 3)

    SilicaListView {
        id: listView
        anchors.fill: parent

        header: DialogHeader {
            acceptText: _selectedQuality + ", " + _selectedFormat
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
            property bool selected: quality === _selectedQuality && format === _selectedFormat
            property bool current: quality === _currentQuality && format === _currentFormat
            height: Theme.itemSizeSmall
            highlighted: down || selected || current
            highlightedColor: selected || down ? _selectedColor : _currentColor
            Label {
                text: format + " format"
                anchors.centerIn: parent
            }
            onClicked: {
                _selectedQuality = quality
                _selectedFormat = format
            }
        }
    }

    function _fillStreamsList() {
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

    function _defineSelected() {
        _currentQuality = _player.streamQualityText();
        _currentFormat = _player.streamFormatText();
        _selectedQuality = _currentQuality
        _selectedFormat = _currentFormat
    }

    function _changeStreams() {
        if (_selectedQuality != _currentQuality || _selectedFormat != _currentFormat)
            _player.changeStream(_selectedQuality, _selectedFormat)
    }

    onAccepted: _changeStreams()

    Connections {
        target: controlPanel
        onClose: close()
    }

    Component.onCompleted: {
        _defineSelected()
        _fillStreamsList()
    }
}
