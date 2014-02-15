/**
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: loadingIndicator

    property Item flickable
    property alias model: connections.target
    property bool stopped: false
    property alias loadingText: progressIndicator.label
    property string defaultErrorText
    property string networkErrorText
    property string parsingErrorText
    property string emptyText
    property string emptyHintText

    parent: flickable.contentItem

    y: flickable.originY + (Screen.height - height) / 2
    width: parent.width - 2*Theme.paddingLarge
    height: progressIndicator.height
    anchors.horizontalCenter: parent.horizontalCenter

    state: "init"

    ProgressBar {
        id: progressIndicator
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width
        indeterminate: true
    }

    Loader {
        id: placeholderLoader
        parent: flickable
    }

    Component {
        id: errorComponent
        ViewPlaceholder {
            text: "An error occured"
            hintText: defaultErrorText

            IconButton {
                anchors.horizontalCenter: parent.horizontalCenter
                y: parent.height + Theme.paddingLarge
                icon.width: Theme.iconSizeLarge
                icon.height: Theme.iconSizeLarge
                icon.asynchronous: true
                icon.source: somaTheme.getIconSource("refresh", "large")
                onClicked: _fetch()
                z: 10
            }
        }
    }

    Component {
        id: emptyComponent
        ViewPlaceholder {
            enabled: flickable.count === 0 && model.isEmpty()
            text: emptyText
            hintText: emptyHintText
        }
    }

    Connections {
        id: connections
        onDataParsed: _changeState("complete")
        onFetchStarted: _changeState("fetching")
        onNetworkError: _displayError("Network error", networkErrorText)
        onParsingError: _displayError("Parsing error", parsingErrorText)
        onDownloadProgress: _updateProgress(bytesReceived, bytesTotal)
    }

    function _fetch() {
        progressIndicator.indeterminate = true
        model.fetch()
    }

    function _updateProgress(bytesReceived, bytesTotal) {
        if (bytesTotal === -1) {
            progressIndicator.indeterminate = true
        } else {
            progressIndicator.indeterminate = false
            progressIndicator.value = bytesReceived / bytesTotal
        }
    }

    function _displayError(text, hintText) {
        _changeState("error")
        placeholderLoader.item.text = text
        placeholderLoader.item.hintText = hintText
    }

    function _changeState(newState) {
        if (stopped) return
        state = newState
    }

    function complete() {
        _changeState("complete")
    }

    states: [
        State {
            name: "init"
            PropertyChanges { target: loadingIndicator; visible: false }
        },
        State {
            name: "fetching"
            PropertyChanges { target: loadingIndicator; visible: true }
            StateChangeScript {
                script: {
                    if (placeholderLoader.status === Loader.Ready)
                        placeholderLoader.item.enabled = false
                }
            }
        },
        State {
            name: "error"
            PropertyChanges { target: loadingIndicator; visible: false }
            StateChangeScript {
                script: {
                    placeholderLoader.sourceComponent = errorComponent
                    placeholderLoader.item.enabled = true
                }
            }
        },
        State {
            name: "complete"
            PropertyChanges { target: loadingIndicator; visible: false }
            StateChangeScript {
                script: {
                    if (model.isEmpty()) {
                        placeholderLoader.sourceComponent = emptyComponent
                    } else if (placeholderLoader.status === Loader.Ready) {
                        placeholderLoader.item.enabled = false
                    }
                }
            }
        }]
}
