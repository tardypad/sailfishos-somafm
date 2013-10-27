import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: loadingIndicator

    property Item flickable
    property alias model: connections.target
    property bool running: false
    property alias loadingText: progressIndicator.label
    property string defaultErrorText
    property string networkErrorText
    property string parsingErrorText
    property bool errorDisplayed: false

    parent: flickable.contentItem

    y: flickable.originY + (Screen.height - height) / 2
    width: parent.width - 2*Theme.paddingLarge
    height: progressIndicator.height
    anchors.horizontalCenter: parent.horizontalCenter

    visible: running

    ProgressBar {
        id: progressIndicator
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width
        indeterminate: true
    }

    Loader {
        id: loader
    }

    Component {
        id: errorComponent
        ViewPlaceholder {
            enabled: true
            text: "An error occured"
            hintText: defaultErrorText
        }
    }

    Connections {
        id: connections
        onDataFetched: stopLoadingAnimation()
        onNetworkError: {
            stopLoadingAnimation()
            displayError("Network error", networkErrorText)
        }
        onParsingError: {
            stopLoadingAnimation()
            displayError("Parsing error", parsingErrorText)
        }
        onDownloadProgress: {
            updateProgress(bytesReceived, bytesTotal)
        }
    }

    function stopLoadingAnimation() {
        running = false
    }

    function updateProgress(bytesReceived, bytesTotal) {
        if (bytesTotal === -1) {
            progressIndicator.indeterminate = true
        } else {
            progressIndicator.indeterminate = false
            progressIndicator.value = bytesReceived / bytesTotal
        }
    }

    function displayError(text, hintText) {
        errorDisplayed = true
        loader.sourceComponent = errorComponent
        if (typeof(text) != "undefined") loader.item.text = text
        if (typeof(hintText) != "undefined") loader.item.hintText = hintText
    }

    Component.onCompleted: loader.parent = flickable
}
