/**
 *
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 **/


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
