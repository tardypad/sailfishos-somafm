import QtQuick 1.1
import Sailfish.Silica 1.0

BackgroundItem {
    id: channelSongsDelegate
    height: theme.itemSizeSmall - 2*theme.paddingSmall

    Label {
        id: dateLabel
        text: Qt.formatDateTime(date, 'hh:mm')
        anchors {
            left: parent.left;
            leftMargin: theme.paddingMedium
            verticalCenter: parent.verticalCenter
        }
        color: theme.secondaryColor
        font.pixelSize: theme.fontSizeSmall
    }

    Column {
        spacing: -theme.paddingSmall
        width: parent.width
        anchors {
            left: dateLabel.right;
            leftMargin: theme.paddingMedium
            verticalCenter: parent.verticalCenter
        }

        Label {
            id: artistLabel
            text: artist
            font.pixelSize: theme.fontSizeSmall
            width: parent.width - dateLabel.width
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            maximumLineCount: 1
            truncationMode: TruncationMode.Fade
        }

        Label {
            id: titleLabel
            text: title
            color: theme.secondaryColor
            font.pixelSize: theme.fontSizeExtraSmall
            width: parent.width - dateLabel.width
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            maximumLineCount: 1
            truncationMode: TruncationMode.Fade
        }
    }
}
