import QtQuick 1.1
import Sailfish.Silica 1.0
import "pages"

ApplicationWindow
{
    initialPage: Component { HomePage { } }
    cover: Qt.resolvedUrl("cover/CoverPage.qml")
}
