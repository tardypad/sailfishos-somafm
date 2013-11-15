import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    width: gridView.cellWidth
    height: gridView.cellHeight

    Image {
        id: imageItem
        width: gridView.cellWidth * 0.6
        height: gridView.cellHeight * 0.6
        anchors {
            top: parent.top
            topMargin: Theme.paddingMedium
            horizontalCenter: parent.horizontalCenter
        }
        smooth: true
        source: "image://theme/icon-l-developer-mode"
        fillMode: Image.PreserveAspectFit
    }

    Label {
        id: contentLabel
        text: content
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: imageItem.bottom
            topMargin: Theme.paddingMedium
            bottom: parent.bottom
            bottomMargin: Theme.paddingMedium
        }
        width: parent.width - 2 * Theme.paddingMedium
        font.pixelSize: Theme.fontSizeExtraSmall
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        maximumLineCount: 2
    }

    onClicked: openItem()

    function openItem() {
        console.log("open "+location+" page in browser")
        Qt.openUrlExternally(location)
    }
}
