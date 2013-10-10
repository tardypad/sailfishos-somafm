import QtQuick 2.0
import Sailfish.Silica 1.0

MenuItem {
    property alias iconSource: icon.source
    property string nextPage
    property bool isReplace

    onClicked: {
        if (isReplace)
            pageStack.replace(nextPage)
        else
            pageStack.push(nextPage)
    }

    Image {
        id: icon
        smooth: true
        height: Theme.iconSizeSmall
        width: Theme.iconSizeSmall
        anchors {
            right: parent.right
            rightMargin: Theme.paddingLarge
            verticalCenter: parent.verticalCenter
        }
        fillMode: Image.PreserveAspectFit
    }
}
