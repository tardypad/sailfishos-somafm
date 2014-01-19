import QtQuick 2.0
import Sailfish.Silica 1.0

MenuItem {
    property alias iconSource: icon.source
    property bool inPullDown: false
    property bool isLeftHanded: false
    property bool _onRightSide: inPullDown || isLeftHanded

    Image {
        id: icon
        height: Theme.iconSizeSmall
        width: Theme.iconSizeSmall
        anchors {
            left: !_onRightSide ? parent.left : undefined
            leftMargin: !_onRightSide ? Theme.paddingLarge : undefined
            right: _onRightSide ? parent.right : undefined
            rightMargin: _onRightSide ? Theme.paddingLarge : undefined
            verticalCenter: parent.verticalCenter
        }
        fillMode: Image.PreserveAspectFit
    }

    Component.onCompleted: isLeftHanded = _settings.leftHanded()
}
