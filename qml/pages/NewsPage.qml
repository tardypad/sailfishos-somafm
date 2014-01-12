import QtQuick 2.0
import Sailfish.Silica 1.0

import "../utils"
import "../delegates"
import "../components"

Page {

    SilicaListView {
        id: listView
        anchors.fill: parent
        header: NewsPageHeader { }
        model: _newsModel
        delegate: NewsListDelegate {  }
        section {
            property: 'dateGroup'
            delegate: SectionHeader {
                text: section
            }
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

        function displayAdditionalElements() {
            headerItem.displayBanner()
            scrollToTop()
            footer = Qt.createComponent("../components/NewsPageFooter.qml")
        }
    }

    Connections {
        target: indicator
        onStateChanged: {
            if (indicator.state === "complete")
                listView.displayAdditionalElements()
        }
    }

    Component.onCompleted: {
        if (!_newsModel.hasDataBeenFetchedOnce())
            _newsModel.fetch()
        else
            listView.displayAdditionalElements()
        _newsModel.sortByDate();
    }

    onStatusChanged: {
        if (status === PageStatus.Inactive)
            _newsModel.abortFetching()
    }
}
