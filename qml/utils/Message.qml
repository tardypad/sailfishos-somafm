/**
 * Copyright (c) 2013-2019 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

import QtQuick 2.0
import Sailfish.Silica 1.0

Rectangle {
    id: messageRect

    property bool _open: false

    color: Theme.highlightBackgroundColor
    width: Screen.width
    height: messageLabel.implicitHeight + 2 * Theme.paddingMedium
    opacity: _open ? 1 : 0
    enabled: _open

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
        _open = true
        messageTimer.start()
    }

    function hide() {
        _open = false
    }

    Behavior on opacity {
        NumberAnimation { }
    }
}
