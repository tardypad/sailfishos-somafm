import QtQuick 2.0
import Sailfish.Silica 1.0

Image {
    id: channelImage

    property alias size: busyIndicator.size

    smooth: size !== BusyIndicatorSize.Small
    fillMode: Image.PreserveAspectCrop
    clip: true

    BusyIndicator {
        id: busyIndicator
        running: channelImage.status === Image.Loading
        anchors.centerIn: parent
    }
}
