import QtQuick 1.1
import Sailfish.Silica 1.0

BackgroundItem {
    id: channelsDelegate
    height: theme.itemSizeLarge

    Image {
        id: channelImage
        smooth: true
        source: imageUrl
        height: parent.height - theme.paddingSmall*2
        width: parent.height - theme.paddingSmall*2
        fillMode: Image.PreserveAspectCrop
        clip: true
        anchors {
            verticalCenter: parent.verticalCenter;
            left: parent.left;
            leftMargin: theme.paddingSmall
        }
    }

    Label {
        id: channelNameLabel
        text: name
        anchors {
            left: channelImage.right;
            leftMargin: theme.paddingSmall;
            top: parent.top
        }
    }

    Label {
        id: channelDescriptionLabel
        text: description
        anchors {
            left: channelImage.right;
            right: parent.right;
            top: channelNameLabel.bottom;
            topMargin: -theme.paddingSmall;
            leftMargin: theme.paddingSmall
        }
        color: theme.secondaryColor
        font.pixelSize: theme.fontSizeExtraSmall
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        truncationMode: TruncationMode.Fade
        maximumLineCount: 2
    }

    onClicked: {
        pageStack.push(Qt.resolvedUrl("ChannelPage.qml"),
                       {
                           'id' : id,
                           'name': name,
                           'description': description,
                           'dj': dj,
                           'imageUrl': imageUrl,
                           'mediumImageUrl': imageMediumUrl,
                           'bigImageUrl': imageBigUrl,
                           'genres': genres,
                           'listeners': listeners,
                           'isFavorite': isFavorite
                       }
                       )
    }
}
