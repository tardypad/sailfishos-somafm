import QtQuick 1.1
import Sailfish.Silica 1.0

MenuItem {
    property alias iconSource: icon.source
    property string nextPage

    onClicked: pageStack.replace(Qt.resolvedUrl(nextPage))

    Image {
        id: icon
        smooth: true
        height: parent.height * 0.7
        width: parent.height * 0.7
        anchors {
            right: parent.right;
            rightMargin: theme.paddingLarge;
            verticalCenter: parent.verticalCenter
        }
        fillMode: Image.PreserveAspectFit
    }
}
