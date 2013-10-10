import QtQuick 2.0
import Sailfish.Silica 1.0

import "qml/pages"
import "qml/cover"

ApplicationWindow
{
    initialPage: Component { HomePage { } }
    cover: CoverPage { }
}
