import QtQuick 1.1
import Sailfish.Silica 1.0

Item {
    height: childrenRect.height + theme.paddingLarge
    width: parent.width

    IconPageHeader {
        id: header
        text: "News"
        iconSource: "qrc:/icons/news"
    }

    Label {
        id: bannerLabel
        text: _newsModel.banner()
        anchors {
            left: parent.left
            leftMargin: theme.paddingLarge
            right: parent.right
            rightMargin: theme.paddingLarge
            top: header.bottom
        }
        color: theme.highlightColor
        font.pixelSize: theme.fontSizeExtraSmall
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
