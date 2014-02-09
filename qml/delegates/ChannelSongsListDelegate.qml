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

import "../utils"

ListItem {
    property int idx: index
    property string artist_d: artist
    property string title_d: title

    menu: listView.contextMenu
    showMenuOnPressAndHold: false // don't use the default showMenu() without properties
    width: listView.width

    Rectangle {
        anchors.fill: parent
        opacity: isCurrent ? 0.1 : 0
        color: Theme.highlightBackgroundColor
    }

    Label {
        id: dateLabel
        text: Qt.formatDateTime(date, 'hh:mm')
        anchors {
            left: parent.left
            leftMargin: Theme.paddingMedium
            verticalCenter: parent.verticalCenter
        }
        color: highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
        font.pixelSize: Theme.fontSizeSmall
    }

    Column {
        anchors {
            left: dateLabel.right
            leftMargin: Theme.paddingMedium
            right: playImage.left
            rightMargin: Theme.paddingMedium
            verticalCenter: parent.verticalCenter
        }

        Label {
            id: artistLabel
            text: artist
            color: highlighted ? Theme.highlightColor : Theme.primaryColor
            font.pixelSize: Theme.fontSizeSmall
            width: parent.width
            truncationMode: TruncationMode.Fade
        }

        Label {
            id: titleLabel
            text: title
            color: highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
            font.pixelSize: Theme.fontSizeExtraSmall
            width: parent.width
            truncationMode: TruncationMode.Fade
        }
    }

    Image {
        id: playImage
        source: somaTheme.getIconSource("play", "small")
        height: Theme.iconSizeSmall
        width: visible ? Theme.iconSizeSmall : 0
        anchors {
            right: bookmarkImage.left
            rightMargin: Theme.paddingMedium
            verticalCenter: parent.verticalCenter
        }
        fillMode: Image.PreserveAspectFit
        visible: isCurrent
    }

    Image {
        id: bookmarkImage
        source: somaTheme.getIconSource("bookmark", "small")
        height: Theme.iconSizeSmall
        width: visible ? Theme.iconSizeSmall : 0
        anchors {
            right: parent.right
            rightMargin: Theme.paddingMedium
            verticalCenter: parent.verticalCenter
        }
        fillMode: Image.PreserveAspectFit
        visible: isBookmark
    }

    onPressAndHold: showMenu({"isBookmark": isBookmark})

    onClicked: {
        if (isCurrent)
            channelPage.play()
    }
}
