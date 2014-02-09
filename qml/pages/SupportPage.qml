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

import "../scripts/ExternalLinks.js" as ExternalLinks

Page {

    SilicaGridView {
        id: gridView
        anchors.fill: parent
        header: SupportPageHeader { }
        delegate: SupportGridDelegate { }
        cellWidth: parent.width / 2
        cellHeight: parent.width / 3

        LoadingIndicator {
            id: indicator
            model: _supportModel
            flickable: gridView
            loadingText: "Loading support items"
            defaultErrorText: "Can't display support items"
            networkErrorText: "Can't download support items list"
            parsingErrorText: "Can't extract support items list"
        }

        VerticalScrollDecorator { flickable: gridView }

        function _displayAdditionalElements() {
            headerItem.displayBanner()
            model = _supportModel
            footer = Qt.createComponent("../components/SupportPageFooter.qml")
        }

        function _browse(link) {
            ExternalLinks.browse(link)
        }
    }

    Connections {
        target: indicator
        onStateChanged: {
            if (indicator.state === "complete")
                gridView._displayAdditionalElements()
        }
    }

    Component.onCompleted: {
        if (!_supportModel.hasDataBeenFetchedOnce())
            _supportModel.fetch()
        else
            gridView._displayAdditionalElements()
    }

    onStatusChanged: {
        if (status === PageStatus.Inactive)
            _supportModel.abortFetching()
    }
}
