import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    property alias text: label.text
    property alias iconSource: icon.source

    height: Theme.itemSizeLarge
    width: parent.width

    Label {
        id: label
        color: Theme.highlightColor
        anchors {
            verticalCenter: parent.verticalCenter
            verticalCenterOffset: 4
            right: icon.left
            rightMargin: Theme.paddingMedium
        }
        font {
            pixelSize: Theme.fontSizeLarge
            family: Theme.fontFamilyHeading
        }
    }

    Image {
        id: icon
        smooth: true
        height: parent.height * 0.5
        width: parent.height * 0.5
        anchors {
            verticalCenter: parent.verticalCenter
            verticalCenterOffset: 4
            right: parent.right
            rightMargin: Theme.paddingLarge
        }
        fillMode: Image.PreserveAspectFit
    }
}
