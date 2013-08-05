import QtQuick 2.0
import Sailfish.Silica 1.0

MenuItem {
    property alias iconSource: icon.source

    Image {
        id: icon
        height: 25
        width: 25
        anchors {
            right: parent.right
            rightMargin: Theme.paddingLarge
            verticalCenter: parent.verticalCenter
        }
        fillMode: Image.PreserveAspectFit
    }
}
