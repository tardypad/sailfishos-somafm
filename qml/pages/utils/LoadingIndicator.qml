import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: loadingIndicator

    property Item flickable
    property alias running: busyIndicator.running
    property alias text: label.text

    parent: flickable.contentItem

    y: flickable.originY + (Screen.height - height) / 2
    width: parent.width - 2*Theme.paddingLarge
    height: busyIndicator.height + label.height
    anchors.horizontalCenter: parent.horizontalCenter

    visible: busyIndicator.running

    BusyIndicator {
        id: busyIndicator
        size: BusyIndicatorSize.Large
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Label {
        id: label
        width: parent.width
        anchors {
            top: busyIndicator.bottom
            topMargin: Theme.paddingMedium
        }
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.Wrap
        color: Theme.highlightColor
        font.pixelSize: Theme.fontSizeMedium
    }
}
