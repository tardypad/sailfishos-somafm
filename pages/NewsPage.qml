import QtQuick 1.1
import Sailfish.Silica 1.0

Page {
    SilicaListView {
        id: listView
        anchors.fill: parent
        header: Item {
            x: theme.paddingLarge
            height: childrenRect.height + theme.paddingLarge
            width: parent.width - 2*theme.paddingLarge

            IconPageHeader {
                id: header
                text: "News"
                iconSource: "qrc:/icons/news"
            }

            Label {
                id: bannerLabel
                text: _newsModel.banner()
                anchors {
                    left: parent.left
                    right: parent.right
                    top: header.bottom
                }
                color: theme.highlightColor
                font.pixelSize: theme.fontSizeExtraSmall
                horizontalAlignment: Text.AlignJustify
                wrapMode: Text.WordWrap
            }
        }
        model: _newsModel
        delegate: NewsDelegate { }

        VerticalScrollDecorator { flickable: listView }
    }
}
