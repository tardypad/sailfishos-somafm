import QtQuick 2.0

QtObject {
    property url websiteUrl: "http://somafm.com"
    property url twitterUrl: "https://twitter.com/somafm"
    property url facebookUrl: "https://www.facebook.com/SomaFM"
    property url flickrUrl: "https://www.flickr.com/photos/somafm"
    property url supportUrl: "http://somafm.com/support"

    function getIconUrl(name) {
        return Qt.resolvedUrl("../../images/icons/"+name+".png")
    }
}
