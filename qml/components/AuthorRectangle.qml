import QtQuick 2.0
import Sailfish.Silica 1.0

Rectangle {
    id: authorRect

    property bool expanded: false

    width: parent.width
    height: workLabel.height + authorLabel.height + linksRow.height + 3 * Theme.paddingMedium + workLabel.topMargin

    MouseArea {
        anchors.fill: parent
        onClicked: expanded = !expanded
    }

    Label {
        id: workLabel

        property int topMargin: Theme.paddingMedium * opacity

        anchors {
            top: parent.top
            topMargin: topMargin
            horizontalCenter: parent.horizontalCenter
        }
        opacity: 0
        height: 0
        width: parent.width - 2 * Theme.paddingMedium
        font.pixelSize: Theme.fontSizeExtraSmall
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        text: "Application definition, design, development, graphics, testing, bugfixing, packaging, maintenance, support,... and much more :-)"
    }

    Label {
        id: authorLabel
        anchors {
            top: workLabel.bottom
            topMargin: Theme.paddingMedium
            horizontalCenter: parent.horizontalCenter
        }
        width: parent.width - 2 * Theme.paddingMedium
        font {
            italic: true
            pixelSize: Theme.fontSizeExtraSmall
        }
        color: Theme.highlightColor
        horizontalAlignment: Text.AlignHCenter
        text: "by Damien Tardy-Panis"
    }

    Row {
        id: linksRow
        anchors {
            top: authorLabel.bottom
            topMargin: Theme.paddingMedium
            horizontalCenter: parent.horizontalCenter
        }
        spacing: Theme.paddingLarge

        IconButton {
            id: twitterButton
            height: Theme.iconSizeMedium
            width: Theme.iconSizeMedium
            icon {
                source: somaTheme.getIconSource("twitter", "medium")
                height: Theme.iconSizeMedium
                fillMode: Image.PreserveAspectFit
            }
            onClicked: Qt.openUrlExternally("https://twitter.com/tardypad")
        }

        IconButton {
            id: githubButton
            height: Theme.iconSizeMedium
            width: Theme.iconSizeMedium
            icon {
                source: somaTheme.getIconSource("github", "medium")
                height: Theme.iconSizeMedium
                fillMode: Image.PreserveAspectFit
            }
            onClicked: Qt.openUrlExternally("https://github.com/tardypad")
        }

        IconButton {
            id: mailButton
            height: Theme.iconSizeMedium
            width: Theme.iconSizeMedium
            icon {
                source: somaTheme.getIconSource("mail", "medium")
                height: Theme.iconSizeMedium
                fillMode: Image.PreserveAspectFit
            }
            onClicked: Qt.openUrlExternally("mailto:damien@tardypad.me?subject=[SomaFM Sailfish app] ")
        }
    }

    states: State {
        name: "shown"; when: expanded
        PropertyChanges { target: workLabel; height: workLabel.implicitHeight }
        PropertyChanges { target: workLabel; opacity: 1 }
    }

    transitions: Transition {
        from: ""; to: "shown"
        reversible: true
        SequentialAnimation {
            NumberAnimation { target: workLabel; property: "height"; duration: 150  }
            NumberAnimation { target: workLabel; property: "opacity"; duration: 100 }
        }
    }
}
