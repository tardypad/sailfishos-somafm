import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: loadingIndicator

    property Item flickable
    property alias model: connections.target
    property alias running: busyIndicator.running
    property alias loadingText: label.text
    property string defaultErrorText
    property string networkErrorText
    property string parsingErrorText
    property bool errorDisplayed: false

    parent: flickable.contentItem

    y: flickable.originY + (Screen.height - height) / 2
    width: parent.width - 2*Theme.paddingLarge
    height: busyIndicator.height + label.height
    anchors.horizontalCenter: parent.horizontalCenter

    visible: busyIndicator.running

    BusyIndicator {
        id: busyIndicator
        size: BusyIndicatorSize.Large
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Label {
        id: label
        width: parent.width
        anchors {
            top: busyIndicator.bottom
            topMargin: Theme.paddingMedium
        }
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.Wrap
        color: Theme.highlightColor
        font.pixelSize: Theme.fontSizeMedium
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
        target: _channelsModel
        onDataFetched: stopLoadingAnimation()
        onNetworkError: {
            stopLoadingAnimation()
            displayError("Network error", networkErrorText)
        }
        onParsingError: {
            stopLoadingAnimation()
            displayError("Parsing error", parsingErrorText)
        }
    }

    function stopLoadingAnimation() {
        indicator.running = false
    }

    function displayError(text, hintText) {
        errorDisplayed = true
        loader.sourceComponent = errorComponent
        if (typeof(text) != "undefined") loader.item.text = text
        if (typeof(hintText) != "undefined") loader.item.hintText = hintText
    }

    Component.onCompleted: loader.parent = flickable
}
