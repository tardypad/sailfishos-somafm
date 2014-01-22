import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    width: gridView.width
    height: supportButton.height + 2*Theme.paddingLarge
    anchors.bottomMargin: Theme.paddingLarge

    Label {
        text: "More info →"
        font.pixelSize: Theme.fontSizeSmall
        anchors {
            right: supportButton.left
            rightMargin: Theme.paddingLarge
            verticalCenter: supportButton.verticalCenter
        }
    }
    IconButton {
        id: supportButton
        height: Theme.iconSizeMedium
        width: Theme.iconSizeMedium
        icon {
            source: somaTheme.getIconSource("web", "medium")
            height: Theme.iconSizeMedium
            fillMode: Image.PreserveAspectFit
        }
        anchors {
            top: parent.top
            topMargin: Theme.paddingLarge
            right: parent.right
            rightMargin: Theme.paddingLarge
        }
        onClicked: {
            console.log("open support page in browser")
            Qt.openUrlExternally(somaTheme.supportUrl)
        }
    }
}
