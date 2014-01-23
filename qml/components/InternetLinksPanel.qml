import QtQuick 2.0
import Sailfish.Silica 1.0

import "../scripts/ExternalLinks.js" as ExternalLinks

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
            onClicked: ExternalLinks.browse(somaTheme.twitterUrl)
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
            onClicked: ExternalLinks.browse(somaTheme.facebookUrl)
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
            onClicked: ExternalLinks.browse(somaTheme.flickrUrl)
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
            onClicked: ExternalLinks.browse(somaTheme.websiteUrl)
        }

        IconButton {
            id: supportButton
            height: iconSize
            width: iconSize
            icon {
                source: somaTheme.getIconSource("websupport", iconSizeName)
                height: iconSize
                fillMode: Image.PreserveAspectFit
            }
            onClicked: ExternalLinks.browse(somaTheme.supportUrl)
        }
    }
}
