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
        id: channelListenersLabel
        text: channelListeners
        anchors {
            right: listenerIcon.left;
            rightMargin: theme.paddingSmall;
            verticalCenter: listenerIcon.verticalCenter
        }
        color: theme.secondaryColor
        font {
            pixelSize: theme.fontSizeExtraSmall * 0.8;
            italic: true
        }
    }

    Image {
        id: listenerIcon
        source: "qrc:/icons/listener"
        smooth: true
        height: channelNameLabel.height * 0.5
        width: channelNameLabel.height * 0.5
        anchors {
            right: parent.right;
            rightMargin: theme.paddingSmall;
            bottom: channelNameLabel.baseline
        }
        fillMode: Image.PreserveAspectFit
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
