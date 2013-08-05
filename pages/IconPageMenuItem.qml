import QtQuick 2.0
import Sailfish.Silica 1.0

MenuItem {
    property alias iconSource: icon.source
    property string nextPage
    property bool isReplace

    onClicked: {
        if (isReplace)
            pageStack.replace(Qt.resolvedUrl(nextPage))
        else
            pageStack.push(Qt.resolvedUrl(nextPage))
    }

    Image {
        id: icon
        smooth: true
        height: parent.height * 0.7
        width: parent.height * 0.7
        anchors {
            right: parent.right
            rightMargin: Theme.paddingLarge
            verticalCenter: parent.verticalCenter
        }
        fillMode: Image.PreserveAspectFit
    }
}
