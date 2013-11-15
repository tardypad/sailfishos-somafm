import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    width: listView.width
    height: supportButton.height + facebookButton.height + 2*Theme.paddingLarge
    anchors.bottomMargin: Theme.paddingLarge

    Button {
        id: supportButton
        text: "Support us"
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: pageStack.push(Qt.resolvedUrl("../SupportPage.qml"))
    }

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
        height: Theme.iconSizeSmall
        width: Theme.iconSizeSmall
        icon {
            source: "qrc:/icon/facebook"
            height: Theme.iconSizeSmall
            fillMode: Image.PreserveAspectFit
        }
        anchors {
            top: supportButton.bottom
            topMargin: Theme.paddingLarge
            right: twitterButton.left
            rightMargin: Theme.paddingLarge
        }
        onClicked: {
            console.log("open facebook page in browser")
            Qt.openUrlExternally(_newsModel.facebookUrl())
        }
    }
    IconButton {
        id: twitterButton
        height: Theme.iconSizeSmall
        width: Theme.iconSizeSmall
        icon {
            source: "qrc:/icon/twitter"
            height: Theme.iconSizeSmall
            fillMode: Image.PreserveAspectFit
        }
        anchors {
            top: supportButton.bottom
            topMargin: Theme.paddingLarge
            right: parent.right
            rightMargin: Theme.paddingLarge
        }
        onClicked: {
            console.log("open twitter page in browser")
            Qt.openUrlExternally(_newsModel.twitterUrl())
        }
    }
}
