import QtQuick 2.0
import Sailfish.Silica 1.0

import "utils"
import "delegates"
import "components"

Page {
    Drawer {
        id: drawer

        open: false
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
                onPressAndHold: if (supportPageHeader.text) drawer.show()
            }

            Loader {
                id: loader
            }

            LoadingIndicator {
                id: indicator
                running: !_newsModel.hasDataBeenFetchedOnce()
                flickable: listView
                text: "Loading news"
            }

            VerticalScrollDecorator { flickable: listView }
        }

        Timer {
            id: timer
            interval: 1000
            onTriggered: {
                supportPageHeader.text = _newsModel.banner()
                drawer.show()
            }
        }

        Connections {
            target: _newsModel
            onDataFetched: {
                indicator.running = false
                timer.start()
            }
            onNetworkError: {
                indicator.running = false
                loader.sourceComponent = errorComponent
                loader.item.text = "Network error"
                loader.item.hintText = "Can't download news"
            }
            onParsingError: {
                indicator.running = false
                loader.sourceComponent = errorComponent
                loader.item.text = "Parsing error"
                loader.item.hintText = "Can't extract news"
            }
        }

        Component {
            id: errorComponent
            ViewPlaceholder {
                enabled: true
                text: "An error occured"
                hintText: "Can't display news"
            }
        }

        Component.onCompleted: {
            if (!_newsModel.hasDataBeenFetchedOnce())
                _newsModel.fetch()
            else
                timer.start()
        }
    }

    onStatusChanged: {
        if (status === PageStatus.Inactive)
            _newsModel.abortFetching()
    }
}
