import QtQuick 2.0
import Sailfish.Silica 1.0

import "utils"

Page {

    SilicaListView {
        id: listView
        anchors.fill: parent
        header: IconPageHeader {
            text: "Settings"
            iconSource: "image://theme/icon-camera-settings"
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
        }

        VerticalScrollDecorator { flickable: listView }
    }

    function fillQualityOptions() {
        var qualityOptions = _channelsModel.streamsQualities();
        for (var i = 0; i < qualityOptions.length; ++i) {
            qualityListModel.append({"text": qualityOptions[i]})
        }
    }

    function fillFormatOptions() {
        var formatOptions = _channelsModel.streamsFormats();
        for (var i = 0; i < formatOptions.length; ++i) {
            formatListModel.append({"text": formatOptions[i]})
        }
    }

    function saveOptions() {
        _settings.saveStreamQuality(qualityComboBox.value);
        _settings.saveStreamFormat(formatComboBox.value);
    }

    Component.onCompleted: {
        fillQualityOptions()
        fillFormatOptions()
    }

    onStatusChanged: {
        if (status === PageStatus.Deactivating) {
            saveOptions()
        }
    }
}
