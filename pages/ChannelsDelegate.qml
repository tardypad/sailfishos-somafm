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
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: theme.paddingSmall
    }

    Label {
        id: channelNameLabel
        text: channelName
        anchors.left: channelImage.right
        anchors.leftMargin: theme.paddingSmall
    }

    Label {
        id: channelDescriptionLabel
        text: channelDescription
        anchors.left: channelImage.right
        anchors.right: parent.right
        anchors.top: channelNameLabel.bottom
        anchors.topMargin: -theme.paddingSmall
        anchors.leftMargin: theme.paddingSmall
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
