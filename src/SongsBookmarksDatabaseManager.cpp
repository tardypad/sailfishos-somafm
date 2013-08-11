#include "SongsBookmarksDatabaseManager.h"

#include <QStringList>
#include <QSqlQuery>
#include <QVariant>

#include "Song.h"

const QString SongsBookmarksDatabaseManager::_songsBookmarkTableName = "song_bookmark";

SongsBookmarksDatabaseManager* SongsBookmarksDatabaseManager::m_instance = NULL;

SongsBookmarksDatabaseManager::SongsBookmarksDatabaseManager(QObject *parent) :
    XmlItemBookmarksDatabaseManager(parent)
{
    init();
}

SongsBookmarksDatabaseManager *SongsBookmarksDatabaseManager::instance()
{
    if (!m_instance) {
        m_instance = new SongsBookmarksDatabaseManager();
    }

    return m_instance;
}

bool SongsBookmarksDatabaseManager::insertBookmark(XmlItem *xmlItem)
{
    QVariant title = xmlItem->data(Song::TitleRole);
    QVariant artist = xmlItem->data(Song::ArtistRole);

    insertBookmarkPreparedQuery.bindValue(":title", title);
    insertBookmarkPreparedQuery.bindValue(":artist", artist);
    insertBookmarkPreparedQuery.bindValue(":channel_id", "poptron");

    bool result = insertBookmarkPreparedQuery.exec();
    int numRowsAffected = insertBookmarkPreparedQuery.numRowsAffected();

    return result && (numRowsAffected == 1);
}

bool SongsBookmarksDatabaseManager::deleteBookmark(XmlItem *xmlItem)
{
    QVariant title = xmlItem->data(Song::TitleRole);
    QVariant artist = xmlItem->data(Song::ArtistRole);

    deleteBookmarkPreparedQuery.bindValue(":title", title);
    deleteBookmarkPreparedQuery.bindValue(":artist", artist);

    bool result = deleteBookmarkPreparedQuery.exec();
    int numRowsAffected = deleteBookmarkPreparedQuery.numRowsAffected();

    return result && (numRowsAffected >= 1);
}

QList<XmlItem *> SongsBookmarksDatabaseManager::retrieveBookmarks()
{
    QList<XmlItem *> xmlItemsBookmarks;
    QSqlQuery query("SELECT title, artist, album, channel_id FROM " + _songsBookmarkTableName);
    QString title, artist, album, channelId;

    while (query.next()) {
        title = query.value(0).toString();
        artist = query.value(1).toString();
        album = query.value(2).toString();
        channelId = query.value(3).toString();

        Song* song = new Song();
        song->setData(title,     Song::TitleRole);
        song->setData(artist,    Song::ArtistRole);
        song->setData(album,     Song::AlbumRole);
        song->setData(channelId, Song::ChannelIdRole);

        xmlItemsBookmarks.append(song);
    }

    return xmlItemsBookmarks;
}

void SongsBookmarksDatabaseManager::checkStructure()
{
    if (!db.isOpen())
        return;

    if (!db.tables().contains(_songsBookmarkTableName)) {
        createStructure();
    }
}

void SongsBookmarksDatabaseManager::prepareQueries()
{
    insertBookmarkPreparedQuery.prepare(
                "INSERT INTO " + _songsBookmarkTableName + " (title, artist, channel_id) \n"
                "VALUES (:title, :artist, :channel_id)"
                );

    deleteBookmarkPreparedQuery.prepare(
                "DELETE FROM " + _songsBookmarkTableName + " \n"
                "WHERE title=:title AND artist=:artist"
                );
}

bool SongsBookmarksDatabaseManager::createStructure()
{
    if (!db.isOpen())
        return false;

    QSqlQuery query("CREATE TABLE " + _songsBookmarkTableName + " (\n"
                    "id         INTEGER     PRIMARY KEY,              -- bookmark id \n"
                    "title      VARCHAR(50) NOT NULL,                 -- song title \n"
                    "artist     VARCHAR(50) NOT NULL,                 -- song artist \n"
                    "album      VARCHAR(50) DEFAULT NULL,             -- song album \n"
                    "channel_id VARCHAR(50) NOT NULL,                 -- song channel id \n"
                    "date       DATETIME    DEFAUT CURRENT_TIMESTAMP, -- date of bookmark creation \n"
                    "UNIQUE (title, artist) \n"
                    ")", db);

    return query.exec();
}
