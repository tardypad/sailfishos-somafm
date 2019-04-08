/**
 * Copyright (c) 2013-2019 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

import QtQuick 2.0
import Sailfish.Silica 1.0

PageHeader {
    property string iconSource

    property int _iconSize: Theme.iconSizeMedium

    state: "reanchored"

    Image {
        id: icon
        smooth: true
        height: _iconSize
        width: _iconSize
        source: somaTheme.getIconSource(iconSource)
        anchors {
            verticalCenter: parent.verticalCenter
            verticalCenterOffset: 4
            right: parent.right
            rightMargin: Theme.paddingLarge
        }
        fillMode: Image.PreserveAspectFit
    }

    states: State {
        name: "reanchored"
        AnchorChanges {
            target: _titleItem
            anchors.right: icon.left
        }
    }
}
