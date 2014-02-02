/**
 *
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 **/


import QtQuick 2.0
import Sailfish.Silica 1.0

import "../scripts/ExternalLinks.js" as ExternalLinks

DockedPanel {
    id: linksPanel

    property int _iconSize: Theme.iconSizeMedium
    property string _iconSizeName: "medium"

    height: column.height + 2*Theme.paddingLarge
    width: column.width + 2*Theme.paddingLarge
    dock: Dock.Left
    anchors.verticalCenter: parent.verticalCenter

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
}
