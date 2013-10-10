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
                onPressAndHold: showSupportBanner();
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
                showSupportBanner();
            }
        }

        Connections {
            target: _newsModel
            onDataFetched: {
                stopLoadingAnimation()
                timer.start()
            }
            onNetworkError: {
                stopLoadingAnimation()
                displayError("Network error", "Can't download news")
            }
            onParsingError: {
                stopLoadingAnimation()
                displayError("Parsing error", "Can't extract news")
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

    function showSupportBanner() {
        if (supportPageHeader.text) drawer.show()
    }

    function displayError(text, hintText) {
        loader.sourceComponent = errorComponent
        if (typeof(text) != "undefined") loader.item.text = text
        if (typeof(hintText) != "undefined") loader.item.hintText = hintText
    }

    function stopLoadingAnimation() {
        indicator.running = false
    }
}
