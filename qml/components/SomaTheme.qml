import QtQuick 2.0
import Sailfish.Silica 1.0

QtObject {
    property url websiteUrl: "http://somafm.com"
    property url twitterUrl: "https://twitter.com/somafm"
    property url facebookUrl: "https://www.facebook.com/SomaFM"
    property url flickrUrl: "https://www.flickr.com/photos/somafm"
    property url supportUrl: "http://somafm.com/support"

    function getIconUrl(name, size) {
        var prefix = size

        switch (size) {
        case "small":
            prefix = 's'
            break;
        case "medium":
            prefix = 'm'
            break
        case "large":
            prefix = 'l'
            break
        }

        return Qt.resolvedUrl("../../images/icons/icon-"+prefix+"-"+name+".png")
    }

    function getIconQrc(name, size) {
        return "qrc:/icon/"+size+"/"+name
    }

    function getImageQrc(name) {
        return "qrc:/image/"+name
    }
}
