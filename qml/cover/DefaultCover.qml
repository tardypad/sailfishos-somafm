import QtQuick 2.0
import Sailfish.Silica 1.0

MainCover {

    content: Image {
        id: channelImage
        source: "qrc:/image/background"
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        verticalAlignment:Image.AlignTop
        horizontalAlignment: Image.AlignHCenter
        smooth: true
        clip: true
    }
}
