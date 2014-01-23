import QtQuick 2.0
import Sailfish.Silica 1.0

DockedPanel {
    id: linksPanel

    property int iconSize: Theme.iconSizeMedium
    property string iconSizeName: "medium"

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
                source: somaTheme.getIconSource("twitter", iconSizeName)
                height: iconSize
                fillMode: Image.PreserveAspectFit
            }
            onClicked: Qt.openUrlExternally(somaTheme.twitterUrl)
        }

        IconButton {
            id: facebookButton
            height: iconSize
            width: iconSize
            icon {
                source: somaTheme.getIconSource("facebook", iconSizeName)
                height: iconSize
                fillMode: Image.PreserveAspectFit
            }
            onClicked: Qt.openUrlExternally(somaTheme.facebookUrl)
        }

        IconButton {
            id: flickrButton
            height: iconSize
            width: iconSize
            icon {
                source: somaTheme.getIconSource("flickr", iconSizeName)
                height: iconSize
                fillMode: Image.PreserveAspectFit
            }
            onClicked: Qt.openUrlExternally(somaTheme.flickrUrl)
        }

        IconButton {
            id: websiteButton
            height: iconSize
            width: iconSize
            icon {
                source: somaTheme.getIconSource("web", iconSizeName)
                height: iconSize
                fillMode: Image.PreserveAspectFit
            }
            onClicked: Qt.openUrlExternally(somaTheme.websiteUrl)
        }

        IconButton {
            id: supportButton
            height: iconSize
            width: iconSize
            icon {
                source: somaTheme.getIconSource("support", iconSizeName)
                height: iconSize
                fillMode: Image.PreserveAspectFit
            }
            onClicked: Qt.openUrlExternally(somaTheme.supportUrl)
        }
    }
}
