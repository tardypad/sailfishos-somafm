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
