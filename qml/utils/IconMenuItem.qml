/**
 * Copyright (c) 2013-2019 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

import QtQuick 2.0
import Sailfish.Silica 1.0

MenuItem {
    property string iconSource
    property bool inPullDown: false

    property int _iconSize: Theme.iconSizeSmall

    property bool _onRightSide: inPullDown

    Image {
        id: icon
        height: _iconSize
        width: _iconSize
        source: somaTheme.getIconSource(iconSource)
        anchors {
            left: !_onRightSide ? parent.left : undefined
            leftMargin: !_onRightSide ? Theme.paddingLarge : undefined
            right: _onRightSide ? parent.right : undefined
            rightMargin: _onRightSide ? Theme.paddingLarge : undefined
            verticalCenter: parent.verticalCenter
        }
        fillMode: Image.PreserveAspectFit
    }
}
