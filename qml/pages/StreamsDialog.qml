import QtQuick 2.0
import Sailfish.Silica 1.0

import "components"

Dialog {
    id: dialog

    property string channelId
    property string selectedQuality
    property string selectedFormat

    SilicaListView {
        id: listView
        anchors.fill: parent
        header: DialogHeader {
            acceptText: selectedQuality + ", " + selectedFormat
            dialog: dialog
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
            height: Theme.itemSizeSmall
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

    Component.onCompleted: fillStreamsList()
}
