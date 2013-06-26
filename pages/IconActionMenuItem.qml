import QtQuick 1.1
import Sailfish.Silica 1.0

MenuItem {
    property alias iconSource: icon.source

    Image {
        id: icon
        height: 25
        width: 25
        anchors {
            right: parent.right
            rightMargin: theme.paddingLarge
            verticalCenter: parent.verticalCenter
        }
        fillMode: Image.PreserveAspectFit
    }
}
