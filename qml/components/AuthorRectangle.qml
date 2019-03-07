/**
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

import QtQuick 2.0
import Sailfish.Silica 1.0

import "../scripts/ExternalLinks.js" as ExternalLinks

Rectangle {
    id: authorRect

    width: parent.width
    height: authorLabel.height + linksRow.height + 3 * Theme.paddingMedium

    Label {
        id: authorLabel
        anchors {
            top: parent.top
            topMargin: Theme.paddingMedium
            horizontalCenter: parent.horizontalCenter
        }
        width: parent.width - 2 * Theme.paddingMedium
        font {
            italic: true
            pixelSize: Theme.fontSizeExtraSmall
        }
        color: Theme.highlightColor
        horizontalAlignment: Text.AlignHCenter
        text: "by Damien Tardy-Panis"
    }

    Row {
        id: linksRow
        anchors {
            top: authorLabel.bottom
            topMargin: Theme.paddingMedium
            horizontalCenter: parent.horizontalCenter
        }
        spacing: Theme.paddingLarge

        IconButton {
            id: githubButton
            height: Theme.iconSizeMedium
            width: Theme.iconSizeMedium
            icon {
                source: somaTheme.getIconSource("github", "medium")
                height: Theme.iconSizeMedium
                fillMode: Image.PreserveAspectFit
            }
            onClicked: ExternalLinks.browse("https://github.com/tardypad")
        }

        IconButton {
            id: mailButton
            height: Theme.iconSizeMedium
            width: Theme.iconSizeMedium
            icon {
                source: somaTheme.getIconSource("mail", "medium")
                height: Theme.iconSizeMedium
                fillMode: Image.PreserveAspectFit
            }
            onClicked: ExternalLinks.mail("damien@tardypad.me", "[SomaFM Sailfish app] ")
        }
    }
}
