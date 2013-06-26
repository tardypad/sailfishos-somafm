import QtQuick 1.1
import Sailfish.Silica 1.0

ViewPlaceholder {
    property alias hintText: hint.text

    Label {
        id: hint
        width: parent.width
        font {
            italic: true
            pixelSize: theme.fontSizeExtraSmall
        }
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignHCenter
        y: parent.height + 2*theme.paddingLarge
    }
}