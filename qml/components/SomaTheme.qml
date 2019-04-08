/**
 * Copyright (c) 2013-2019 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

import QtQuick 2.0
import Sailfish.Silica 1.0

QtObject {
    property url websiteUrl: "http://somafm.com"
    property url supportUrl: "http://somafm.com/support"

    function getIconSource(name, type) {
        if (type === "cover")
            return Qt.resolvedUrl("../../images/icons/cover-"+name+".png")

        return "qrc:/icon/"+name
    }

    function getImageSource(name) {
        return "qrc:/image/"+name
    }
}
