#include "songsModel.h"

#include <QXmlStreamReader>

#include "song.h"
#include "songsBookmarksManager.h"

SongsModel::SongsModel(QObject *parent) :
    XmlModel(new Song(), parent)
{
    m_bookmarksManager = SongsBookmarksManager::instance();
    connect(m_bookmarksManager, SIGNAL(bookmarkAdded(QString,QString)), this, SLOT(addToBookmarks(QString,QString)));
    connect(m_bookmarksManager, SIGNAL(bookmarkRemoved(QString,QString)), this, SLOT(removeFromBookmarks(QString,QString)));
}

SongsModel::~SongsModel()
{
}

void SongsModel::setChannelId(QString channelId)
{
    setResourceUrl(QUrl("http://somafm.com/songs/" + channelId + ".xml"));
}

void SongsModel::setDataSong(QString artist, QString title, const QVariant &value, int role)
{
    for (int row = 0; row < m_list.size(); ++row) {
        QString itemArtist = m_list.at(row)->data(Song::ArtistRole).toString();
        QString itemTitle = m_list.at(row)->data(Song::TitleRole).toString();
        if (itemArtist == artist && itemTitle == title) {
            setData(index(row) ,value, role);
        }
    }
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

    if (m_bookmarksManager->isBookmark(artist, title)) {
        song->setData(true, Song::IsBookmarkRole);
    }

    return song;
}

void SongsModel::addToBookmarks(QString artist, QString title)
{
    setDataSong(artist, title, true, Song::IsBookmarkRole);
}

void SongsModel::removeFromBookmarks(QString artist, QString title)
{
    setDataSong(artist, title, false, Song::IsBookmarkRole);
}