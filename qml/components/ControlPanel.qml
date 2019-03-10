/**
 * Copyright (c) 2013-2019 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

import QtQuick 2.0
import Sailfish.Silica 1.0

import "../utils"

import "../scripts/DurationFormatter.js" as DurationFormatter

DockedPanel {
    id: controlPanel

    property alias isPushMenuActive: pushUpMenu.active

    signal close

    width: parent.width
    height: backgroundItem.height
    contentHeight: height
    flickableDirection: Flickable.VerticalFlick
    dock: Dock.Bottom

    BackgroundItem {
        id: backgroundItem
        width: parent.width
        height: Theme.itemSizeExtraLarge

        Rectangle {
            anchors.fill: parent
            color: Theme.secondaryHighlightColor
        }

        ChannelImage {
            id: channelImage
            source: control.channelImageUrl
            size: BusyIndicatorSize.Small
            height: parent.height
            width: height
            anchors {
                left: parent.left
                top: parent.top
            }
        }

        Label {
            id: channelLabel
            text: control.channelName
            anchors {
                left: channelImage.right
                leftMargin: Theme.paddingMedium
                right: mediaButtonPause.left
                rightMargin: Theme.paddingMedium
                top: parent.top
                topMargin: Theme.paddingSmall
            }
            truncationMode: TruncationMode.Fade
            horizontalAlignment: implicitWidth < width ? Text.AlignHCenter : Text.AlignLeft
        }

        Label {
            id: artistLabel
            text: control.artist
            anchors {
                left: channelImage.right
                leftMargin: Theme.paddingMedium
                right: mediaButtonPause.left
                rightMargin: Theme.paddingMedium
                bottom: titleLabel.top
                bottomMargin: -Theme.paddingSmall
            }
            truncationMode: TruncationMode.Fade
            font.pixelSize: Theme.fontSizeExtraSmall
            horizontalAlignment: implicitWidth < width ? Text.AlignHCenter : Text.AlignLeft
        }

        Label {
            id: titleLabel
            text: control.title
            anchors {
                left: channelImage.right
                leftMargin: Theme.paddingMedium
                right: mediaButtonPause.left
                rightMargin: Theme.paddingMedium
                bottom: parent.bottom
                bottomMargin: Theme.paddingMedium
            }
            truncationMode: TruncationMode.Fade
            font{
                pixelSize: Theme.fontSizeExtraSmall
                italic: true
            }
            horizontalAlignment: implicitWidth < width ? Text.AlignHCenter : Text.AlignLeft
        }

        ProgressCircle {
            id: progressIndicator
            width: Theme.iconSizeLarge
            height: Theme.iconSizeLarge
            anchors.centerIn: mediaButtonPause
            Timer {
                id: progressTimer
                property bool isRunning
                running: window.applicationActive && isRunning
                interval: 250
                repeat: true
                onTriggered: progressIndicator.value = (progressIndicator.value + 1/240) % 1.0
            }
        }

        IconButton {
            id: mediaButtonPause
            icon.width: Theme.iconSizeMedium
            icon.height: Theme.iconSizeMedium
            anchors {
                right: parent.right
                rightMargin: Theme.paddingLarge
                verticalCenter: parent.verticalCenter
            }
            icon.asynchronous: true
            icon.source: somaTheme.getIconSource("pause", "medium")
            highlighted: true
            visible: false
            onClicked: control.pause()
        }

        IconButton {
            id: mediaButtonPlay
            icon.width: Theme.iconSizeMedium
            icon.height: Theme.iconSizeMedium
            anchors {
                right: parent.right
                rightMargin: Theme.paddingLarge
                verticalCenter: parent.verticalCenter
            }
            icon.asynchronous: true
            icon.source: somaTheme.getIconSource("play", "medium")
            onClicked: control.play()
        }

        onClicked: _goToChannelPage()
    }

    PushUpMenu {
        id: pushUpMenu
        IconMenuItem {
            iconSource: "stream"
            text: "Change channel quality/format"
            onClicked: _openStreamsDialog()
            visible: !_isDialogPage(pageStack.currentPage)
        }
        IconMenuItem {
            iconSource: !control.isSongBookmark ? "bookmark" : "unbookmark"
            text: !control.isSongBookmark ? "Add song to bookmarks" : "Remove song from bookmarks"
            onClicked: {
                if (!control.isSongBookmark) {
                    control.addSongToBookmarks()
                } else {
                    control.removeSongFromBookmarks()
                }
            }
        }
        IconMenuItem {
            iconSource: "timer"
            text: !control.isSleepTimerRunning ? "Sleep timer" : "Stop sleep in " + DurationFormatter.formatRemainingTime(control.sleepTimeRemaining)
            onClicked: {
                if (!control.isSleepTimerRunning) {
                    _openSleepTimerDialog()
                } else {
                    remorse.execute(qsTr("Sleep timer gets stopped"), function() {
                        control.stopSleepTimer();
                    }, 3000)
                }
            }
            visible: !_isDialogPage(pageStack.currentPage)
        }
    }

    RemorsePopup {
        id: remorse
        parent: controlPanel.parent
        anchors.bottom: parent.bottom
    }

    Timer {
        id: remainingSleepTimeTimer
        interval: 30000
        repeat: true
        running: control.isSleepTimerRunning
        onTriggered: control.sleepTimeRemaining -= 30
    }

    function reinitProgressIndicator() {
        progressIndicator.value = 0
        progressIndicator.inAlternateCycle = true
    }

    function startProgressTimer() {
        progressTimer.start()
    }

    function stopProgressTimer() {
        progressTimer.stop()
    }

    function _goToChannelPage() {
        if (_isDialogPage(pageStack.currentPage))
            return

        var url = Qt.resolvedUrl("../pages/ChannelPage.qml")
        var properties = {"id": control.channelId}

        var currentPage = pageStack.currentPage
        if (_isChannelPage(currentPage)) {
            if (currentPage.id !== control.channelId) {
                currentPage.stopUpdates()
                pageStack.replace(url, properties)
            }
            return
        }

        var previousChannelPage = pageStack.find(_isChannelPage)
        if (previousChannelPage) {
            pageStack.replaceAbove(pageStack.previousPage(previousChannelPage), url, properties)
            return
        }

        pageStack.push(url, properties)
    }

    function _isChannelPage(page) {
        return page.objectName === "ChannelPage"
    }

    function _isDialogPage(page) {
        return page.objectName.match(/Dialog/);
    }

    function _openStreamsDialog() {
        if (_isDialogPage(pageStack.currentPage))
            return

        pageStack.push(Qt.resolvedUrl("../pages/StreamsDialog.qml"),
            {"channelId": control.channelId})
    }

    function _openSleepTimerDialog() {
        if (_isDialogPage(pageStack.currentPage))
            return

        pageStack.push(Qt.resolvedUrl("../pages/SleepTimerDialog.qml"));
    }

    Connections {
        target: control
        onStateChanged: {
            if (control.state === "playing") {
                mediaButtonPlay.visible = false;
                mediaButtonPause.visible = true;
                progressTimer.isRunning = true;
                channelLabel.color = Theme.highlightColor;
                artistLabel.color = Theme.highlightColor;
                titleLabel.color = Theme.highlightColor;
            } else {
                mediaButtonPlay.visible = true;
                mediaButtonPause.visible = false;
                progressTimer.isRunning = false;
                channelLabel.color = Theme.primaryColor;
                artistLabel.color = Theme.primaryColor;
                titleLabel.color = Theme.primaryColor;
            }
        }
    }

    onOpenChanged: {
        if (!open) {
            if (control.state === "playing")
                control.pause()
            close()
        }
    }
}
