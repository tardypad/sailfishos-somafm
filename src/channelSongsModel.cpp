#include "channelSongsModel.h"

#include <QXmlStreamReader>

#include "channelSong.h"
#include "bookmarksManager.h"

ChannelSongsModel::ChannelSongsModel(QObject *parent) :
    XmlModel(new ChannelSong(), parent)
{
    m_bookmarksManager = BookmarksManager::instance();
    connect(m_bookmarksManager, SIGNAL(bookmarkAdded(QString,QString)), this, SLOT(addToBookmarks(QString,QString)));
    connect(m_bookmarksManager, SIGNAL(bookmarkRemoved(QString,QString)), this, SLOT(removeFromBookmarks(QString,QString)));
}

ChannelSongsModel::~ChannelSongsModel()
{
}

void ChannelSongsModel::setChannelId(QString channelId)
{
    setResourceUrl(QUrl("http://somafm.com/songs/" + channelId + ".xml"));
}

void ChannelSongsModel::setDataSong(QString artist, QString title, const QVariant &value, int role)
{
    for (int row = 0; row < m_list.size(); ++row) {
        QString itemArtist = m_list.at(row)->data(ChannelSong::ArtistRole).toString();
        QString itemTitle = m_list.at(row)->data(ChannelSong::TitleRole).toString();
        if (itemArtist == artist && itemTitle == title) {
            setData(index(row) ,value, role);
        }
    }
}

XmlItem* ChannelSongsModel::parseXmlItem()
{
    ChannelSong* channelSong = new ChannelSong();
    QString title = "";
    QString artist = "";
    QString album = "";
    QDateTime datetime = QDateTime();

    while (!(m_xmlReader->isEndElement() && m_xmlReader->name() == m_xmlItemPrototype->xmlTag())) {
        m_xmlReader->readNext();
        if (m_xmlReader->isStartElement()) {
            if (m_xmlReader->name() == "title") {
                m_xmlReader->readNext();
                title = m_xmlReader->text().toString();
            } else if (m_xmlReader->name() == "artist") {
                m_xmlReader->readNext();
                artist = m_xmlReader->text().toString();
            } else if (m_xmlReader->name() == "album") {
                m_xmlReader->readNext();
                album = m_xmlReader->text().toString();
            } else if (m_xmlReader->name() == "date") {
                m_xmlReader->readNext();
                int timestamp = m_xmlReader->text().toString().toInt();
                datetime = QDateTime::fromTime_t(timestamp);
            }
        }
    }

    channelSong->setData(title, ChannelSong::TitleRole);
    channelSong->setData(artist, ChannelSong::ArtistRole);
    channelSong->setData(album, ChannelSong::AlbumRole);
    channelSong->setData(datetime, ChannelSong::DateRole);

    if (m_bookmarksManager->isBookmark(artist, title)) {
        channelSong->setData(true, ChannelSong::IsBookmarkRole);
    }

    return channelSong;
}

void ChannelSongsModel::addToBookmarks(QString artist, QString title)
{
    setDataSong(artist, title, true, ChannelSong::IsBookmarkRole);
}

void ChannelSongsModel::removeFromBookmarks(QString artist, QString title)
{
    setDataSong(artist, title, false, ChannelSong::IsBookmarkRole);
}
