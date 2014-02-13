/**
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

import QtQuick 2.0
import Sailfish.Silica 1.0

ChannelsListDelegate {

    Label {
        id: channelListenersLabel
        text: listeners
        anchors {
            right: listenerIcon.left
            rightMargin: Theme.paddingSmall
            verticalCenter: listenerIcon.verticalCenter
        }
        color: highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
        font {
            pixelSize: Theme.fontSizeExtraSmall * 0.8;
            italic: true
        }
    }

    Image {
        id: listenerIcon
        source: somaTheme.getIconSource("listener", "small")
        smooth: true
        height: Theme.iconSizeSmall * 0.8
        width: height
        anchors {
            top: column.top
            topMargin: Theme.paddingSmall
            right: parent.right
            rightMargin: Theme.paddingMedium
        }
        opacity: 0.1 + (listeners / maximumListeners) * 0.9
        fillMode: Image.PreserveAspectFit
    }
}
