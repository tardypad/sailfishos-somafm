import QtQuick 2.0
import Sailfish.Silica 1.0

DockedPanel {
    id: linksPanel

    property int iconSize: Theme.iconSizeSmall

    height: column.height + 2*Theme.paddingLarge
    width: column.width + 2*Theme.paddingLarge
    dock: Dock.Left
    anchors.verticalCenter: parent.verticalCenter

    Column {
        id: column
        spacing: Theme.paddingLarge
        anchors.centerIn: parent

        IconButton {
            id: twitterButton
            height: iconSize
            width: iconSize
            icon {
                source: somaTheme.getIconQrc("twitter", "small")
                height: iconSize
                fillMode: Image.PreserveAspectFit
            }
            onClicked: {
                console.log("open twitter page in browser")
                Qt.openUrlExternally(somaTheme.twitterUrl)
            }
        }

        IconButton {
            id: facebookButton
            height: iconSize
            width: iconSize
            icon {
                source: somaTheme.getIconQrc("facebook", "small")
                height: iconSize
                fillMode: Image.PreserveAspectFit
            }
            onClicked: {
                console.log("open facebook page in browser")
                Qt.openUrlExternally(somaTheme.facebookUrl)
            }
        }

        IconButton {
            id: flickrButton
            height: iconSize
            width: iconSize
            icon {
                source: somaTheme.getIconQrc("flickr", "small")
                height: iconSize
                fillMode: Image.PreserveAspectFit
            }
            onClicked: {
                console.log("open flickr page in browser")
                Qt.openUrlExternally(somaTheme.flickrUrl)
            }
        }

        IconButton {
            id: websiteButton
            height: iconSize
            width: iconSize
            icon {
                source: somaTheme.getIconQrc("web", "small")
                height: iconSize
                fillMode: Image.PreserveAspectFit
            }
            onClicked: {
                console.log("open home page in browser")
                Qt.openUrlExternally(somaTheme.websiteUrl)
            }
        }

        IconButton {
            id: supportButton
            height: iconSize
            width: iconSize
            icon {
                source: somaTheme.getIconQrc("support", "small")
                height: iconSize
                fillMode: Image.PreserveAspectFit
            }
            onClicked: {
                console.log("open support page in browser")
                Qt.openUrlExternally(somaTheme.supportUrl)
            }
        }
    }
}
