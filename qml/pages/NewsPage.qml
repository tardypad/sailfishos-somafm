import QtQuick 2.0
import Sailfish.Silica 1.0

import "utils"
import "delegates"
import "components"

Page {
    Drawer {
        id: drawer

        open: false
        anchors.fill: parent
        backgroundSize: Screen.height / 2

        background: Item {
            anchors.fill: parent
            height: supportPageHeader.height

            NewsPageHeader {
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
                title: "News"
                iconSource: "qrc:/icon/news"
            }
            model: _newsModel
            delegate: NewsListDelegate {  }
            section {
                property: 'dateGroup'
                delegate: SectionHeader {
                    text: section
                }
            }

            MouseArea {
                anchors.fill: parent
                propagateComposedEvents: true
                onClicked: {
                    mouse.accepted = false
                    drawer.hide()
                }
                onPressAndHold: showSupportBanner();
            }

            LoadingIndicator {
                id: indicator
                model: _newsModel
                flickable: listView
                loadingText: "Loading news"
                defaultErrorText: "Can't display news"
                networkErrorText: "Can't download news"
                parsingErrorText: "Can't extract news"
            }

            VerticalScrollDecorator { flickable: listView }
        }

        Timer {
            id: timer
            interval: 1000
            onTriggered: {
                if (indicator.state != "complete")
                    return
                supportPageHeader.text = _newsModel.banner()
                showSupportBanner();
                listView.footer = Qt.createComponent("components/NewsPageFooter.qml")
            }
        }

        Connections {
            target: _newsModel
            onDataParsed: timer.start()
        }

        Component.onCompleted: {
            if (!_newsModel.hasDataBeenFetchedOnce())
                _newsModel.fetch()
            else
                timer.start()
            _newsModel.sortByDate();
        }
    }

    onStatusChanged: {
        if (status === PageStatus.Inactive)
            _newsModel.abortFetching()
    }

    function showSupportBanner() {
        if (supportPageHeader.text) drawer.show()
    }
}
