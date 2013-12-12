import QtQuick 2.0
import Sailfish.Silica 1.0

Rectangle {
    id: messageRect

    property bool open: false

    color: Theme.highlightColor
    width: Screen.width
    height: messageLabel.implicitHeight + 2 * Theme.paddingMedium
    opacity: open ? 1 : 0
    enabled: open

    Label {
        id: messageLabel
        anchors.centerIn: parent
        width: parent.width - 2 * Theme.paddingLarge
        font.pixelSize: Theme.fontSizeExtraSmall
        horizontalAlignment: Text.AlignHCenter
    }

    Timer {
        id: messageTimer
        interval: 5000
        onTriggered: hide()
    }

    MouseArea {
        anchors.fill: parent
        onClicked: hide()
    }

    function show(text) {
        messageLabel.text = text
        open = true
        messageTimer.start()
    }

    function hide() {
        open = false
    }

    Behavior on opacity {
        NumberAnimation { }
    }
}
