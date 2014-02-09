/**
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

import QtQuick 2.0
import Sailfish.Silica 1.0

import "../scripts/ExternalLinks.js" as ExternalLinks

Item {
    width: gridView.width
    height: supportButton.height + 2*Theme.paddingLarge
    anchors.bottomMargin: Theme.paddingLarge

    Label {
        text: "More info →"
        font.pixelSize: Theme.fontSizeSmall
        anchors {
            right: supportButton.left
            rightMargin: Theme.paddingLarge
            verticalCenter: supportButton.verticalCenter
        }
    }
    IconButton {
        id: supportButton
        height: Theme.iconSizeMedium
        width: Theme.iconSizeMedium
        icon {
            source: somaTheme.getIconSource("websupport", "medium")
            height: Theme.iconSizeMedium
            fillMode: Image.PreserveAspectFit
        }
        anchors {
            top: parent.top
            topMargin: Theme.paddingLarge
            right: parent.right
            rightMargin: Theme.paddingLarge
        }
        onClicked: ExternalLinks.browse(somaTheme.supportUrl)
    }
}
