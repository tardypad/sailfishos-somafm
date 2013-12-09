import QtQuick 2.0
import Sailfish.Silica 1.0

import "../utils"

Rectangle {
    property alias text: bannerLabel.text

    height: childrenRect.height + Theme.paddingLarge
    width: parent.width
    color: Theme.rgba(Theme.secondaryHighlightColor, 0.5)

    IconPageHeader {
        id: header
        title: "Support"
        iconSource: "qrc:/icon/support"
    }

    Label {
        id: bannerLabel
        anchors {
            left: parent.left
            leftMargin: Theme.paddingLarge
            right: parent.right
            rightMargin: Theme.paddingLarge
            top: header.bottom
        }
        font.pixelSize: Theme.fontSizeExtraSmall
        horizontalAlignment: Text.AlignJustify
        wrapMode: Text.WordWrap
    }

    Button {
        text: "Support us"
        anchors {
            top: bannerLabel.bottom
            horizontalCenter: parent.horizontalCenter
        }
        onClicked: pageStack.push(Qt.resolvedUrl("../SupportPage.qml"))
    }
}
