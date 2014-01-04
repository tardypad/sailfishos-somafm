import QtQuick 2.0
import Sailfish.Silica 1.0

import "../utils"

Item {
    property alias text: bannerLabel.text

    height: childrenRect.height
    width: listView.width

    IconPageHeader {
        id: pageHeader
        title: "News"
        iconSource: "qrc:/icon/news"
    }

    Label {
        id: bannerLabel
        anchors {
            top: pageHeader.bottom
            horizontalCenter: parent.horizontalCenter
        }
        color: Theme.highlightColor
        width: parent.width - 2 * Theme.paddingLarge
        font.pixelSize: Theme.fontSizeExtraSmall
        horizontalAlignment: Text.AlignJustify
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
    }

    Button {
        id: supportButton
        text: "Support us"
        anchors {
            top: bannerLabel.bottom
            horizontalCenter: parent.horizontalCenter
        }
        onClicked: pageStack.push(Qt.resolvedUrl("../pages/SupportPage.qml"))
    }

    Connections {
        target: _newsModel
        onDataParsed: getBannerText()
    }

    Component.onCompleted: getBannerText()

    function getBannerText() {
        bannerLabel.text = _newsModel.banner()
    }
}
