import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    id: channelsDelegate
    width: gridView.cellWidth
    height: gridView.cellHeight

    Image {
        id: channelImage
        width: gridView.cellWidth - Theme.paddingSmall*2
        height: gridView.cellHeight - Theme.paddingSmall*2
        sourceSize {
            width: gridView.cellWidth - Theme.paddingSmall*2
            height: gridView.cellHeight - Theme.paddingSmall*2
        }
        smooth: true
        source: (imageMediumUrl != "") ? imageMediumUrl : imageBigUrl
        anchors {
            verticalCenter: parent.verticalCenter
            horizontalCenter: parent.horizontalCenter
        }
        fillMode: Image.PreserveAspectCrop
        clip: true
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
                           'isFavorite': isBookmark
                       }
                       )
    }
}
