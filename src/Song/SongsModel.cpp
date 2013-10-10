#include "SongsModel.h"

#include <QDebug>
#include <QXmlStreamReader>

#include "../SomaFM.h"
#include "Song.h"
#include "../Channel/Channel.h"
#include "SongsBookmarksManager.h"

SongsModel::SongsModel(QObject *parent) :
    XmlItemModel(new Song(), parent),
    m_channel(NULL)
{
    m_bookmarksManager = SongsBookmarksManager::instance();
    connect(m_bookmarksManager, SIGNAL(bookmarkAdded(XmlItem*)), this, SLOT(addToBookmarks(XmlItem*)));
    connect(m_bookmarksManager, SIGNAL(bookmarkRemoved(XmlItem*)), this, SLOT(removeFromBookmarks(XmlItem*)));
}

SongsModel::~SongsModel()
{
}

void SongsModel::setChannel(XmlItem *channel)
{
    m_channel = (Channel*) channel;

    QString channelId = m_channel->data(Channel::IdRole).toString();
    setResourceUrl(SomaFM::channelSongsUrl(channelId));
}

bool SongsModel::stopParsing(XmlItem *xmlItem)
{
    QDateTime date = xmlItem->data(Song::DateRole).toDateTime();

    return date.addSecs(3600) < QDateTime::currentDateTime();
}

XmlItem* SongsModel::parseXmlItem()
{
    Song* song = new Song();
    QString title = "";
    QString artist = "";
    QString album = "";
    QDateTime datetime = QDateTime();
    QString channelId = m_channel->data(Channel::IdRole).toString();
    QString channelName = m_channel->data(Channel::NameRole).toString();
    QUrl channelImageUrl = m_channel->data(Channel::ImageUrlRole).toString();

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

    song->setData(title, Song::TitleRole);
    song->setData(artist, Song::ArtistRole);
    song->setData(album, Song::AlbumRole);
    song->setData(datetime, Song::DateRole);
    song->setData(channelId, Song::ChannelIdRole);
    song->setData(channelName, Song::ChannelNameRole);
    song->setData(channelImageUrl, Song::ChannelImageUrlRole);

    if (m_bookmarksManager->isBookmark(song)) {
        song->setData(true, Song::IsBookmarkRole);
    }

    return song;
}
