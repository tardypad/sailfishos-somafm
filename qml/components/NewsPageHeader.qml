/**
 * Copyright (c) 2013-2019 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

import QtQuick 2.0
import Sailfish.Silica 1.0

import "../utils"

import "../scripts/ExternalLinks.js" as ExternalLinks

Item {
    height: childrenRect.height
    width: listView.width

    IconPageHeader {
        id: pageHeader
        title: "News"
        iconSource: "news"
    }

    Label {
        id: bannerLabel
        anchors {
            top: pageHeader.bottom
            horizontalCenter: parent.horizontalCenter
        }
        color: Theme.highlightColor
        width: parent.width - 2 * Theme.paddingLarge
        font.pixelSize: Theme.fontSizeExtraSmall
        horizontalAlignment: Text.AlignJustify
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
    }

    Button {
        id: supportButton
        text: "Support us"
        visible: false
        anchors {
            top: bannerLabel.bottom
            horizontalCenter: parent.horizontalCenter
        }
        onClicked: ExternalLinks.browse(somaTheme.supportUrl)
    }

    function displayBanner() {
        bannerLabel.text = _newsModel.banner()
        supportButton.visible = true
    }
}
