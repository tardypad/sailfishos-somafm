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
        var color
        if (Theme.colorScheme == 0)
            color = "light"
        else
            color = "dark"

        if (type === "cover")
            return Qt.resolvedUrl("../../images/icons/"+color+"/cover_"+name+".png")

        return "qrc:/icon/"+color+"/"+name
    }

    function getImageSource(name) {
        return "qrc:/image/"+name
    }
}
