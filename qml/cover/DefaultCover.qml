/**
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

import QtQuick 2.0
import Sailfish.Silica 1.0

MainCover {

    content: Image {
        id: channelImage
        source: somaTheme.getImageSource("background")
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        verticalAlignment:Image.AlignTop
        horizontalAlignment: Image.AlignHCenter
        smooth: true
        clip: true
    }
}
