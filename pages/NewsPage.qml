import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    Drawer {
        id: drawer

        open: true
        backgroundSize: Screen.height / 2
        anchors.fill: parent

        background: Item {
            anchors.fill: parent

            SupportPageHeader {
                id: supportPageHeader
                anchors.fill: parent
            }

            MouseArea {
                anchors.fill: parent
                propagateComposedEvents: true
                onClicked: {
                    mouse.accepted = false
                    drawer.hide()
                }
            }
        }

        SilicaListView {
            id: listView
            anchors.fill: parent
            header: IconPageHeader {
                id: header
                text: "News"
                iconSource: "qrc:/icon/news"
            }
            model: _newsModel
            delegate: NewsDelegate { }
            section {
                property: 'dateGroup'
                delegate: SectionHeader {
                    text: section
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: drawer.hide()
                onPressAndHold: drawer.show()
            }

            VerticalScrollDecorator { flickable: listView }
        }

    }
}
