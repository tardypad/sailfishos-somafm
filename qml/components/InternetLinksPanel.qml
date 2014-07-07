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
    id: linksPanel

    property int _iconSize: Theme.iconSizeMedium
    property string _iconSizeName: "medium"

    height: column.height + 2*Theme.paddingLarge
    width: column.width + 2*Theme.paddingLarge
    anchors.verticalCenter: parent.verticalCenter
    x: -width
    color: "transparent"

    Column {
        id: column
        spacing: Theme.paddingLarge
        anchors.centerIn: parent

        IconButton {
            id: twitterButton
            height: _iconSize
            width: _iconSize
            icon {
                source: somaTheme.getIconSource("twitter", _iconSizeName)
                height: _iconSize
                fillMode: Image.PreserveAspectFit
            }
            onClicked: ExternalLinks.browse(somaTheme.twitterUrl)
        }

        IconButton {
            id: facebookButton
            height: _iconSize
            width: _iconSize
            icon {
                source: somaTheme.getIconSource("facebook", _iconSizeName)
                height: _iconSize
                fillMode: Image.PreserveAspectFit
            }
            onClicked: ExternalLinks.browse(somaTheme.facebookUrl)
        }

        IconButton {
            id: flickrButton
            height: _iconSize
            width: _iconSize
            icon {
                source: somaTheme.getIconSource("flickr", _iconSizeName)
                height: _iconSize
                fillMode: Image.PreserveAspectFit
            }
            onClicked: ExternalLinks.browse(somaTheme.flickrUrl)
        }

        IconButton {
            id: websiteButton
            height: _iconSize
            width: _iconSize
            icon {
                source: somaTheme.getIconSource("web", _iconSizeName)
                height: _iconSize
                fillMode: Image.PreserveAspectFit
            }
            onClicked: ExternalLinks.browse(somaTheme.websiteUrl)
        }

        IconButton {
            id: supportButton
            height: _iconSize
            width: _iconSize
            icon {
                source: somaTheme.getIconSource("websupport", _iconSizeName)
                height: _iconSize
                fillMode: Image.PreserveAspectFit
            }
            onClicked: ExternalLinks.browse(somaTheme.supportUrl)
        }
    }

    function show() {
        x = 0
    }

    function hide() {
        x = -width
    }

    Behavior on x {
        NumberAnimation { }
    }

}
