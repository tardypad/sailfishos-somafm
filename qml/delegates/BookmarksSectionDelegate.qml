/**
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

import QtQuick 2.0
import Sailfish.Silica 1.0

import "../components"

Item {
    height: sectionHeader.height
    width: parent.width

    SectionHeader {
        id: sectionHeader
        text: listView.channelsData[section] ? listView.channelsData[section]["name"] : ""
        anchors {
            right: channelImage.left
            rightMargin: Theme.paddingMedium
        }
    }

    ChannelImage {
        id: channelImage
        size: BusyIndicatorSize.Small
        source: listView.channelsData[section] ? listView.channelsData[section]["image_url"] : ""
        height: sectionHeader.height
        width: sectionHeader.height
        anchors {
            right: parent.right
            rightMargin: Theme.paddingMedium
        }
    }
}
