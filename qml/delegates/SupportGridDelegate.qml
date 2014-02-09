/**
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

import QtQuick 2.0
import Sailfish.Silica 1.0

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

    onClicked: gridView._browse(location)
}
