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
    id: newsDelegate
    x: Theme.paddingLarge
    width: parent.width - 2*Theme.paddingLarge
    height: dateLabel.height + contentLabel.height + Theme.paddingLarge

    Label {
        id: dateLabel
        text: Qt.formatDateTime(date, 'MMM, d')
        font {
            pixelSize: Theme.fontSizeExtraSmall
            italic: true
        }
        color: Theme.secondaryColor
        anchors {
            left: parent.left
            top: parent.top
        }
    }

    Label {
        id: contentLabel
        text: content
        font.pixelSize: Theme.fontSizeExtraSmall
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignJustify
        anchors {
            top: dateLabel.bottom
            left: parent.left
            right: parent.right
        }
        linkColor: Theme.highlightColor
        onLinkActivated: {
            var url = /^https?:\/\//i.test(link) ? link : somaTheme.websiteUrl + link
            ExternalLinks.browse(url)
        }
    }
}
