import QtQuick 1.1
import Sailfish.Silica 1.0

BackgroundItem {
    id: channelsDelegate
    height: theme.itemSizeLarge

    Image {
        id: channelImage
        smooth: true
        source: channelImageUrl
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
        text: channelName
        anchors {
            left: channelImage.right;
            leftMargin: theme.paddingSmall;
            top: parent.top
        }
    }

    Label {
        id: channelDescriptionLabel
        text: channelDescription
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
                           'name': channelName,
                           'description': channelDescription,
                           'dj': channelDj,
                           'imageUrl': channelImageUrl,
                           'mediumImageUrl': channelImageMediumUrl,
                           'bigImageUrl': channelImageBigUrl,
                           'genre': channelGenre,
                           'listeners': channelListeners
                       }
                       )
    }
}
