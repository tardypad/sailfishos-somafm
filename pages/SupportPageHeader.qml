import QtQuick 2.0
import Sailfish.Silica 1.0

Rectangle {
    property alias text: bannerLabel.text

    height: childrenRect.height + Theme.paddingLarge
    width: parent.width
    color: Theme.rgba(Theme.secondaryHighlightColor, 0.5)

    IconPageHeader {
        id: header
        text: "Support"
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
        text: "Donate"
        anchors {
            top: bannerLabel.bottom
            horizontalCenter: parent.horizontalCenter
        }
        onClicked: {
            console.log("open support page in browser")
            Qt.openUrlExternally(_newsModel.supportUrl())
        }
    }
}
