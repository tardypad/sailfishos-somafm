/**
 * Copyright (c) 2013-2019 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

import QtQuick 2.0
import Sailfish.Silica 1.0

import "../scripts/ExternalLinks.js" as ExternalLinks

Item {
    height: childrenRect.height
    width: listView.width

    PageHeader {
        id: header
        title: _name

        Image {
            id: favoriteImage
            source: somaTheme.getIconSource("favorite")
            height: Theme.iconSizeSmall
            width: Theme.iconSizeSmall
            anchors {
                right: header._titleItem.left
                rightMargin: Theme.paddingSmall
                verticalCenter: header._titleItem.verticalCenter
            }
            fillMode: Image.PreserveAspectFit
            visible: _isFavorite
        }
    }

    ChannelImage {
        id: channelImage
        size: BusyIndicatorSize.Medium
        source: _imageUrl
        height: Theme.itemSizeLarge * 2
        width: Theme.itemSizeLarge * 2
        anchors {
            left: parent.left
            top: header.bottom
        }
    }

    Label {
        id: channelDescriptionLabel
        text: _description
        anchors {
            left: channelImage.right
            right: parent.right
            top: header.bottom
            rightMargin: Theme.paddingLarge
            leftMargin: Theme.paddingMedium
        }
        font.pixelSize: Theme.fontSizeExtraSmall
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        truncationMode: TruncationMode.Fade
        maximumLineCount: 4
    }

    Label {
        id: channelDjLabel
        text: "by " + _dj
        anchors {
            top: channelDescriptionLabel.bottom
            right: mailButton.left
            rightMargin: Theme.paddingSmall
        }
        color: Theme.highlightColor
        font {
            pixelSize: Theme.fontSizeExtraSmall
            italic: true
        }
        visible: _dj
        horizontalAlignment: Text.AlignRight

        MouseArea {
            anchors.fill: parent
            onClicked: _mailDj()
        }
    }

    IconButton {
        id: mailButton
        anchors {
            right: parent.right
            rightMargin: Theme.paddingLarge
            verticalCenter: channelDjLabel.verticalCenter
        }
        height: Theme.iconSizeSmall / 2
        width: Theme.iconSizeSmall / 2
        icon {
            source: somaTheme.getIconSource("mail")
            height: Theme.iconSizeSmall / 2
            fillMode: Image.PreserveAspectFit
        }
        visible: _dj
        onClicked: _mailDj()
    }

    function _mailDj() {
        if (_djMail)
            ExternalLinks.mail(_djMail, "["+_name+"] ")
    }
}
