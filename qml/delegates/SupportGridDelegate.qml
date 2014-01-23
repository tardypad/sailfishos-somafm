import QtQuick 2.0
import Sailfish.Silica 1.0

import "../scripts/ExternalLinks.js" as ExternalLinks

BackgroundItem {
    width: gridView.cellWidth
    height: gridView.cellHeight

    Rectangle {
        anchors.centerIn: parent
        width: parent.width - 2 * Theme.paddingSmall
        height: parent.height - 2 * Theme.paddingSmall
        color: Theme.rgba(Theme.highlightBackgroundColor, Theme.highlightBackgroundOpacity / 3)
    }

    Label {
        id: contentLabel
        text: content
        anchors.centerIn: parent
        width: parent.width - 2 * Theme.paddingMedium
        font.pixelSize: Theme.fontSizeExtraSmall
        color: highlighted ? Theme.highlightColor : Theme.primaryColor
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        maximumLineCount: 3
    }

    onClicked: ExternalLinks.browse(location)
}
