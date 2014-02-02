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
