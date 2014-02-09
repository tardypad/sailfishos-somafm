/**
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

import QtQuick 2.0
import Sailfish.Silica 1.0

import "../utils"
import "../delegates"
import "../components"

import "../scripts/ExternalLinks.js" as ExternalLinks

Page {

    SilicaListView {
        id: listView
        anchors.fill: parent
        header: NewsPageHeader { }
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

        function _displayAdditionalElements() {
            headerItem.displayBanner()
            model = _newsModel
            footer = Qt.createComponent("../components/NewsPageFooter.qml")
        }

        function _browse(link) {
            var url = /^https?:\/\//i.test(link) ? link : somaTheme.websiteUrl + link
            ExternalLinks.browse(url)
        }
    }

    Connections {
        target: indicator
        onStateChanged: {
            if (indicator.state === "complete")
                listView._displayAdditionalElements()
        }
    }

    Component.onCompleted: {
        if (!_newsModel.hasDataBeenFetchedOnce())
            _newsModel.fetch()
        else
            listView._displayAdditionalElements()
        _newsModel.sortByDate();
    }

    onStatusChanged: {
        if (status === PageStatus.Inactive)
            _newsModel.abortFetching()
    }
}
