import QtQuick 2.0
import Sailfish.Silica 1.0

MenuItem {
    property alias iconSource: icon.source
    property bool inPullDown: false

    Image {
        id: icon
        height: Theme.iconSizeSmall
        width: Theme.iconSizeSmall
        anchors {
            left: !inPullDown ? parent.left : undefined
            leftMargin: !inPullDown ? Theme.paddingLarge : undefined
            right: inPullDown ? parent.right : undefined
            rightMargin: inPullDown ? Theme.paddingLarge : undefined
            verticalCenter: parent.verticalCenter
        }
        fillMode: Image.PreserveAspectFit
    }
}
