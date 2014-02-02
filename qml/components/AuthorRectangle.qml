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

Rectangle {
    id: authorRect

    property bool _expanded: false

    width: parent.width
    height: workLabel.height + authorLabel.height + linksRow.height + 3 * Theme.paddingMedium + workLabel.topMargin

    MouseArea {
        anchors.fill: parent
        onClicked: _expanded = !_expanded
    }

    Label {
        id: workLabel

        property int topMargin: Theme.paddingMedium * opacity

        anchors {
            top: parent.top
            topMargin: topMargin
            horizontalCenter: parent.horizontalCenter
        }
        opacity: 0
        height: 0
        width: parent.width - 2 * Theme.paddingMedium
        font.pixelSize: Theme.fontSizeExtraSmall
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        text: "Application definition, design, development, graphics, testing, bugfixing, packaging, maintenance, support,... and much more :-)"
    }

    Label {
        id: authorLabel
        anchors {
            top: workLabel.bottom
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
            id: twitterButton
            height: Theme.iconSizeMedium
            width: Theme.iconSizeMedium
            icon {
                source: somaTheme.getIconSource("twitter", "medium")
                height: Theme.iconSizeMedium
                fillMode: Image.PreserveAspectFit
            }
            onClicked: ExternalLinks.browse("https://twitter.com/tardypad")
        }

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

    states: State {
        name: "shown"; when: _expanded
        PropertyChanges { target: workLabel; height: workLabel.implicitHeight }
        PropertyChanges { target: workLabel; opacity: 1 }
    }

    transitions: Transition {
        from: ""; to: "shown"
        reversible: true
        SequentialAnimation {
            NumberAnimation { target: workLabel; property: "height"; duration: 150  }
            NumberAnimation { target: workLabel; property: "opacity"; duration: 100 }
        }
    }
}
