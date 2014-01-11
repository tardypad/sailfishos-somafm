import QtQuick 2.0
import Sailfish.Silica 1.0

import "pages"
import "cover"
import "components"
import "utils"

ApplicationWindow
{
    id: window

    initialPage: Component { HomePage { } }
    cover: DefaultCover { }
    bottomMargin: controlPanel.visibleSize

    Loader {
        id: messageLoader
        anchors.bottom: controlPanel.top
    }

    Component {
        id: messageComponent
        Message { }
    }

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

    function showMessage(text) {
        if (messageLoader.status === Loader.Null)
            messageLoader.sourceComponent = messageComponent

        messageLoader.item.show(text)
    }

    SomaTheme {
        id: somaTheme
    }

    Timer {
        id: refreshTimer
        running: window.applicationActive
        repeat: true
        interval: 20000
        onTriggered: _refreshModel.fetch()
    }
}
