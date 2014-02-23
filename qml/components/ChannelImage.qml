/**
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

import QtQuick 2.0
import Sailfish.Silica 1.0

Image {
    id: channelImage

    property alias size: busyIndicator.size

    smooth: true
    fillMode: Image.PreserveAspectCrop
    clip: true

    BusyIndicator {
        id: busyIndicator
        running: channelImage.status === Image.Loading
        anchors.centerIn: parent
    }
}
