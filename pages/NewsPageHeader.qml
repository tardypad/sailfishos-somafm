import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    height: childrenRect.height + Theme.paddingLarge
    width: parent.width

    IconPageHeader {
        id: header
        text: "News"
        iconSource: "qrc:/icon/news"
    }

    Label {
        id: bannerLabel
        text: _newsModel.banner()
        anchors {
            left: parent.left
            leftMargin: Theme.paddingLarge
            right: parent.right
            rightMargin: Theme.paddingLarge
            top: header.bottom
        }
        color: Theme.highlightColor
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
        onClicked: Qt.openUrlExternally(_newsModel.supportUrl())
    }
}
