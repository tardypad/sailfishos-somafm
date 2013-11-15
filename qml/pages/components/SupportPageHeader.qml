import QtQuick 2.0
import Sailfish.Silica 1.0

import "../utils"

Item {
    height: childrenRect.height
    width: gridView.width

    IconPageHeader {
        id: pageHeader
        text: "Support"
        iconSource: "qrc:/icon/support"
    }

    Label {
        id: bannerLabel
        anchors {
            top: pageHeader.bottom
            horizontalCenter: parent.horizontalCenter
        }
        color: Theme.highlightColor
        width: parent.width - 2 * Theme.paddingLarge
        font.pixelSize: Theme.fontSizeSmall
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
    }

    Connections {
        target: _supportModel
        onDataParsed: getBannerText()
    }

    Component.onCompleted: getBannerText()

    function getBannerText() {
        bannerLabel.text = _supportModel.banner()
    }
}
