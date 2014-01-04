import QtQuick 2.0
import Sailfish.Silica 1.0

PageHeader {
    property alias iconSource: icon.source

    state: "reanchored"

    Image {
        id: icon
        smooth: true
        height: Theme.iconSizeMedium
        width: Theme.iconSizeMedium
        anchors {
            verticalCenter: parent.verticalCenter
            verticalCenterOffset: 4
            right: parent.right
            rightMargin: Theme.paddingLarge
        }
        fillMode: Image.PreserveAspectFit
    }

    states: State {
        name: "reanchored"
        AnchorChanges {
            target: _titleItem
            anchors.right: icon.left
        }
    }
}
