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

            XmlRole { name: "channelName";     query: "title/string()" }
            XmlRole { name: "channelImageUrl"; query: "image/string()" }
        }
        delegate: BackgroundItem {
                Image {
                    id: channelImage
                    source: channelImageUrl
                    height: parent.height - 10
                    width: parent.height - 10
                    fillMode: Image.PreserveAspectCrop
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                }

                Label {
                    text: channelName
                    anchors.left: channelImage.right
                    anchors.leftMargin: 5
                }
        }

        ScrollDecorator { }
    }
}
