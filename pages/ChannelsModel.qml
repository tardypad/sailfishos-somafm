import QtQuick 1.1
import Sailfish.Silica 1.0

XmlListModel
{
    id: channelsModel
    source: "http://somafm.com/channels.xml"
    query: "/channels/channel"

    XmlRole { name: "channelName";           query: "title/string()" }
    XmlRole { name: "channelDescription";    query: "description/string()" }
    XmlRole { name: "channelImageUrl";       query: "image/string()" }
    XmlRole { name: "channelImageMediumUrl"; query: "largeimage/string()" }
    XmlRole { name: "channelDj";             query: "dj/string()" }
    XmlRole { name: "channelGenre";         query: "genre/string()" }
    XmlRole { name: "channelListeners";      query: "listeners/string()" }
}
