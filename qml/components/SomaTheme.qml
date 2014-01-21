import QtQuick 2.0
import Sailfish.Silica 1.0

QtObject {
    property url websiteUrl: "http://somafm.com"
    property url twitterUrl: "https://twitter.com/somafm"
    property url facebookUrl: "https://www.facebook.com/SomaFM"
    property url flickrUrl: "https://www.flickr.com/photos/somafm"
    property url supportUrl: "http://somafm.com/support"

    function getIconSource(name, size) {
        if (size === "cover")
            return Qt.resolvedUrl("../../images/icons/icon-cover-"+name+".png")

        return "qrc:/icon/"+size+"/"+name
    }

    function getImageSource(name) {
        return "qrc:/image/"+name
    }
}
