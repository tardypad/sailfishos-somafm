/**
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

import QtQuick 2.0

Rectangle {
    id: banner

    property alias spacing: row.spacing

    color: "black"

    Row {
        id: row
        anchors.centerIn: parent

        Image {
            anchors.verticalCenter: parent.verticalCenter
            source: somaTheme.getImageSource("logo")
            smooth: true
            fillMode: Image.PreserveAspectFit
            height: banner.height * 0.8
            width: banner.width * 0.2
        }

        Image {
            anchors.verticalCenter: parent.verticalCenter
            source: somaTheme.getImageSource("name")
            smooth: true
            fillMode: Image.PreserveAspectFit
            height: banner.height * 0.8
            width: banner.width * 0.6
        }
    }
}
