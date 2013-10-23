import QtQuick 2.0
import Sailfish.Silica 1.0

import "pages"
import "cover"
import "pages/components"

ApplicationWindow
{
    initialPage: Component { HomePage { } }
    cover: CoverPage { }
    bottomMargin: controlPanel.visibleSize

    ControlPanel {
        id: controlPanel
    }
}
