import QtQuick 2.0
import Sailfish.Silica 1.0

import "../pages/components"

CoverBackground {

    property alias content: content.children

    Banner {
        id: banner
        width: parent.width
        height: parent.height * 0.2
        spacing: Theme.paddingMedium
    }

    Item {
        id: content
        anchors {
            top: banner.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
    }
}
