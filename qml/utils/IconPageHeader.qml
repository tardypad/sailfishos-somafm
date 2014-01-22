import QtQuick 2.0
import Sailfish.Silica 1.0

PageHeader {
    property string iconSource
    property int iconSize: Theme.iconSizeMedium
    property string iconSizeName: "medium"

    state: "reanchored"

    Image {
        id: icon
        smooth: true
        height: iconSize
        width: iconSize
        source: somaTheme.getIconSource(iconSource, iconSizeName)
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
