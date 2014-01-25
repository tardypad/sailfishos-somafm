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
                text: "Accessibility"
            }

            TextSwitch {
                id: leftHandedTextSwitch
                text: "Left-handed"
            }
        }

        VerticalScrollDecorator { flickable: listView }
    }

    function _defineQualityOptions() {
        var qualityOptions = _channelsModel.streamsQualities();
        var selectedQuality = _settings.streamQuality();
        for (var i = 0; i < qualityOptions.length; ++i) {
            qualityListModel.append({"text": qualityOptions[i]})
            if (qualityOptions[i] === selectedQuality) {
                qualityComboBox.currentIndex = i
            }
        }
    }

    function _defineFormatOptions() {
        var formatOptions = _channelsModel.streamsFormats();
        var selectedFormat = _settings.streamFormat();
        for (var i = 0; i < formatOptions.length; ++i) {
            formatListModel.append({"text": formatOptions[i]})
            if (formatOptions[i] === selectedFormat) {
                formatComboBox.currentIndex = i
            }
        }
    }

    function _defineLeftHanded() {
        leftHandedTextSwitch.checked = _settings.leftHanded()
    }

    function _saveOptions() {
        _settings.saveStreamQuality(qualityComboBox.value);
        _settings.saveStreamFormat(formatComboBox.value);
        _settings.saveLeftHanded(leftHandedTextSwitch.checked);
    }

    Component.onCompleted: {
        _defineQualityOptions()
        _defineFormatOptions()
        _defineLeftHanded()
    }

    onStatusChanged: {
        if (status === PageStatus.Deactivating) {
            _saveOptions()
        }
    }
}
