import QtQuick 2.0
import Sailfish.Silica 1.0

import "qml/pages"
import "qml/cover"
import "qml/pages/components"

ApplicationWindow
{
    initialPage: Component { HomePage { } }
    cover: CoverPage { }
    bottomMargin: controlPanel.enabled ? controlPanel.height : 0

    ControlPanel {
        id: controlPanel
        anchors.bottom: parent.bottom
    }
}
