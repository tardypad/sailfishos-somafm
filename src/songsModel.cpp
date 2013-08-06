#include "songsModel.h"

#include <QXmlStreamReader>

#include "somaFM.h"
#include "song.h"
#include "songsBookmarksManager.h"

SongsModel::SongsModel(QObject *parent) :
    XmlModel(new Song(), parent),
    m_channelId("")
{
    m_bookmarksManager = SongsBookmarksManager::instance();
    connect(m_bookmarksManager, SIGNAL(bookmarkAdded(XmlItem*)), this, SLOT(addToBookmarks(XmlItem*)));
    connect(m_bookmarksManager, SIGNAL(bookmarkRemoved(XmlItem*)), this, SLOT(removeFromBookmarks(XmlItem*)));
}

SongsModel::~SongsModel()
{
}

void SongsModel::setChannelId(QString channelId)
{
    m_channelId = channelId;
    setResourceUrl(SomaFM::channelSongsUrl(channelId));
}

XmlItem* SongsModel::parseXmlItem()
{
    Song* song = new Song();
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

    song->setData(title, Song::TitleRole);
    song->setData(artist, Song::ArtistRole);
    song->setData(album, Song::AlbumRole);
    song->setData(datetime, Song::DateRole);

    if (m_bookmarksManager->isBookmark(song)) {
        song->setData(true, Song::IsBookmarkRole);
    }

    return song;
}
