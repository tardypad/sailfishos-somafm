import QtQuick 1.1
import Sailfish.Silica 1.0

Page {
    SilicaListView {
        anchors.fill: parent
        header: PageHeader {
            title: "Channels"
        }
        model: XmlListModel
        {
            source: "http://somafm.com/channels.xml"
            query: "/channels/channel"

            XmlRole { name: "channelName"; query: "title/string()" }
        }
        delegate: BackgroundItem {
            Label {
                text: channelName
            }
        }
    }
}
