import QtQuick 2.0
import Sailfish.Silica 1.0

MenuItem {
    property string iconSource
    property bool inPullDown: false

    property int _iconSize: Theme.iconSizeSmall
    property string _iconSizeName: "small"

    property bool _isLeftHanded: false
    property bool _onRightSide: inPullDown || _isLeftHanded

    Image {
        id: icon
        height: _iconSize
        width: _iconSize
        source: somaTheme.getIconSource(iconSource, _iconSizeName)
        anchors {
            left: !_onRightSide ? parent.left : undefined
            leftMargin: !_onRightSide ? Theme.paddingLarge : undefined
            right: _onRightSide ? parent.right : undefined
            rightMargin: _onRightSide ? Theme.paddingLarge : undefined
            verticalCenter: parent.verticalCenter
        }
        fillMode: Image.PreserveAspectFit
    }

    Component.onCompleted: _isLeftHanded = _settings.leftHanded()
}
