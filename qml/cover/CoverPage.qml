import QtQuick 2.0
import Sailfish.Silica 1.0

CoverBackground {
    Rectangle {
        anchors.fill: parent
        color: "black"
        opacity: 0.8
    }

    CoverPlaceholder {
        text: "SomaFM"
        icon.source: "qrc:/image/logo"
    }
}
