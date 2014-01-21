import QtQuick 2.0

Rectangle {
    id: banner

    property alias spacing: row.spacing

    color: "black"

    Row {
        id: row
        anchors.centerIn: parent

        Image {
            anchors.verticalCenter: parent.verticalCenter
            source: somaTheme.getImageQrc("logo")
            smooth: true
            fillMode: Image.PreserveAspectFit
            height: banner.height * 0.8
            width: banner.width * 0.2
        }

        Image {
            anchors.verticalCenter: parent.verticalCenter
            source: somaTheme.getImageQrc("name")
            smooth: true
            fillMode: Image.PreserveAspectFit
            height: banner.height * 0.8
            width: banner.width * 0.6
        }
    }
}
