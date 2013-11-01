import QtQuick 2.0
import Sailfish.Silica 1.0

import "pages"
import "cover"
import "pages/components"

ApplicationWindow
{
    initialPage: Component { HomePage { } }
    cover: DefaultCover { }
    bottomMargin: controlPanel.visibleSize

    ControlPanel {
        id: controlPanel
    }

    Connections {
        target: controlPanel
        onOpenChanged: {
            if (controlPanel.open)
                cover = Qt.resolvedUrl("cover/PlayerCover.qml")
            else
                cover = Qt.resolvedUrl("cover/DefaultCover.qml")
        }
    }
}
