import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    height: sectionHeader.height
    width: parent.width

    SectionHeader {
        id: sectionHeader
        text: listView.channelsData[section] ? listView.channelsData[section]["name"] : ""
        anchors {
            right: channelImage.left
            rightMargin: Theme.paddingMedium
        }
    }

    Image {
        id: channelImage
        smooth: false
        source: listView.channelsData[section] ? listView.channelsData[section]["image_url"] : ""
        height: sectionHeader.height
        width: sectionHeader.height
        fillMode: Image.PreserveAspectCrop
        clip: true
        anchors {
            right: parent.right
            rightMargin: Theme.paddingMedium
        }

        BusyIndicator {
            size: BusyIndicatorSize.Small
            running: channelImage.status === Image.Loading
            anchors.centerIn: parent
        }
    }
}
