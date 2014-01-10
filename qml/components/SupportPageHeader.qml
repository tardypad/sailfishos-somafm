import QtQuick 2.0
import Sailfish.Silica 1.0

import "../utils"

Item {
    height: childrenRect.height
    width: gridView.width

    IconPageHeader {
        id: pageHeader
        title: "Support"
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
        horizontalAlignment: Text.AlignJustify
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
    }

    function displayBanner() {
        bannerLabel.text = _supportModel.banner()
    }
}