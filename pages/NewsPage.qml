import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    SilicaListView {
        id: listView
        anchors.fill: parent
        header: NewsPageHeader { }
        model: _newsModel
        delegate: NewsDelegate { }
        section {
            property: 'dateGroup'
            delegate: SectionHeader {
                text: section
            }
        }

        VerticalScrollDecorator { flickable: listView }
    }
}
