/**
 * Copyright (c) 2013-2019 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

import QtQuick 2.0
import Sailfish.Silica 1.0

import "../utils"

Page {

    SilicaListView {
        id: listView
        anchors.fill: parent
        header: IconPageHeader {
            title: "Settings"
            iconSource: "settings"
        }
        model: VisualItemModel {

            SectionHeader {
                text: "Streams"
            }

            ComboBox {
                id: qualityComboBox
                width: parent.width
                label: "Preferred quality"
                menu: ContextMenu {
                    Repeater {
                        model: ListModel { id: qualityListModel }
                        MenuItem { text: model.text }
                    }
                }
            }

            Label {
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
                visible: qualityComboBox._menuOpen
                height: visible ? implicitHeight : 0
            }

            ComboBox {
                id: formatComboBox
                width: parent.width
                label: "Preferred format"
                menu: ContextMenu {
                    Repeater {
                        model: ListModel { id: formatListModel }
                        MenuItem { text: model.text }
                    }
                }
            }

            SectionHeader {
                text: "Display"
            }

            TextSwitch {
                id: songCoverTextSwitch
                text: "Artist and song in cover"
            }

            SectionHeader {
                text: "Accessibility"
            }

            TextSwitch {
                id: leftHandedTextSwitch
                text: "Left-handed"
            }
        }

        VerticalScrollDecorator { flickable: listView }
    }

    function _fillQualityOptions() {
        var qualityOptions = _channelsModel.streamsQualities()
        for (var i = 0; i < qualityOptions.length; ++i) {
            qualityListModel.append({"text": qualityOptions[i]})
        }
    }

    function _fillFormatOptions() {
        var formatOptions = _channelsModel.streamsFormats()
        for (var i = 0; i < formatOptions.length; ++i) {
            formatListModel.append({"text": formatOptions[i]})
        }
    }

    function _defineSelectedQuality() {
        var selectedQuality = _settings.streamQuality()
        for (var i = 0; i < qualityListModel.count; ++i) {
            if (qualityListModel.get(i).text === selectedQuality) {
                qualityComboBox.currentIndex = i
                return
            }
        }
    }

    function _defineSelectedFormat() {
        var selectedFormat = _settings.streamFormat()
        for (var i = 0; i < formatListModel.count; ++i) {
            if (formatListModel.get(i).text === selectedFormat) {
                formatComboBox.currentIndex = i
                return
            }
        }
    }

    function _defineSongCover() {
        songCoverTextSwitch.checked = _settings.songCover()
    }

    function _defineLeftHanded() {
        leftHandedTextSwitch.checked = _settings.leftHanded()
    }

    function _saveOptions() {
        _settings.saveStreamQuality(qualityComboBox.value)
        _settings.saveStreamFormat(formatComboBox.value)
        _settings.saveSongCover(songCoverTextSwitch.checked)
        _settings.saveLeftHanded(leftHandedTextSwitch.checked)
    }

    Component.onCompleted: {
        _fillQualityOptions()
        _fillFormatOptions()
        _defineSongCover()
        _defineLeftHanded()
        afterResetTimer.start()
    }

    // hack: on device, currentIndex needs to be set after ComboBox updateCurrentTimer
    Timer {
        id: afterResetTimer
        interval: 1
        onTriggered: {
            _defineSelectedQuality()
            _defineSelectedFormat()
        }
    }

    onStatusChanged: {
        if (status === PageStatus.Deactivating) {
            _saveOptions()
        }
    }
}
