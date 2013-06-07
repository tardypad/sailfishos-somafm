import QtQuick 1.1
import Sailfish.Silica 1.0

BackgroundItem {
    id: channelsDelegate
    width: gridView.cellWidth
    height: gridView.cellHeight

    Image {
        id: channelImage
        width: gridView.cellWidth - theme.paddingSmall*2
        height: gridView.cellHeight - theme.paddingSmall*2
        sourceSize.width: gridView.cellWidth - theme.paddingSmall*2
        sourceSize.height: gridView.cellHeight - theme.paddingSmall*2
        smooth: true
        source: channelImageMediumUrl ? channelImageMediumUrl : channelImageBigUrl
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.PreserveAspectCrop
        clip: true
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
