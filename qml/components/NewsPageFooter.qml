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
    width: listView.width
    height: facebookButton.height + 2*Theme.paddingLarge
    anchors.bottomMargin: Theme.paddingLarge

    Label {
        text: "More news →"
        font.pixelSize: Theme.fontSizeSmall
        anchors {
            right: facebookButton.left
            rightMargin: Theme.paddingLarge
            verticalCenter: facebookButton.verticalCenter
        }
    }
    IconButton {
        id: facebookButton
        height: Theme.iconSizeMedium
        width: Theme.iconSizeMedium
        icon {
            source: somaTheme.getIconSource("facebook", "medium")
            height: Theme.iconSizeMedium
            fillMode: Image.PreserveAspectFit
        }
        anchors {
            top: parent.top
            topMargin: Theme.paddingLarge
            right: twitterButton.left
            rightMargin: Theme.paddingLarge
        }
        onClicked: ExternalLinks.browse(somaTheme.facebookUrl)
    }
    IconButton {
        id: twitterButton
        height: Theme.iconSizeMedium
        width: Theme.iconSizeMedium
        icon {
            source: somaTheme.getIconSource("twitter", "medium")
            height: Theme.iconSizeMedium
            fillMode: Image.PreserveAspectFit
        }
        anchors {
            top: parent.top
            topMargin: Theme.paddingLarge
            right: parent.right
            rightMargin: Theme.paddingLarge
        }
        onClicked: ExternalLinks.browse(somaTheme.twitterUrl)
    }
}
