import QtQuick 1.1
import Sailfish.Silica 1.0

Item {
    property alias text: label.text
    property alias iconSource: icon.source

    height: theme.itemSizeLarge
    width: parent.width

    Label {
        id: label
        color: theme.highlightColor
        anchors {
            verticalCenter: parent.verticalCenter
            verticalCenterOffset: 4
            right: icon.left
            rightMargin: theme.paddingMedium
        }
        font {
            pixelSize: theme.fontSizeLarge
            family: theme.fontFamilyHeading
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
            rightMargin: theme.paddingLarge
        }
        fillMode: Image.PreserveAspectFit
    }
}
