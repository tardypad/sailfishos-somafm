#include "SongsBookmarksDatabaseManager.h"

#include <QStringList>
#include <QSqlQuery>
#include <QVariant>
#include <QDateTime>

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
    QVariant album = xmlItem->data(Song::AlbumRole);
    QVariant channelId = xmlItem->data(Song::ChannelIdRole);
    QVariant channelName = xmlItem->data(Song::ChannelNameRole);
    QVariant channelImageUrl = xmlItem->data(Song::ChannelImageUrlRole);

    insertBookmarkPreparedQuery.bindValue(":title", title);
    insertBookmarkPreparedQuery.bindValue(":artist", artist);
    insertBookmarkPreparedQuery.bindValue(":album", album);
    insertBookmarkPreparedQuery.bindValue(":channel_id", channelId);
    insertBookmarkPreparedQuery.bindValue(":channel_name", channelName);
    insertBookmarkPreparedQuery.bindValue(":channel_image_url", channelImageUrl);
    insertBookmarkPreparedQuery.bindValue(":date", QDateTime::currentDateTime());

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
    QSqlQuery query("SELECT title, artist, album, channel_id, channel_name, channel_image_url, date FROM " + _songsBookmarkTableName);
    QVariant title, artist, album, channelId, channelName, channelImageUrl, date;

    while (query.next()) {
        title = query.value(0);
        artist = query.value(1);
        album = query.value(2);
        channelId = query.value(3);
        channelName = query.value(4);
        channelImageUrl = query.value(5);
        date = query.value(6);

        Song* song = new Song();
        song->setData(title,           Song::TitleRole);
        song->setData(artist,          Song::ArtistRole);
        song->setData(album,           Song::AlbumRole);
        song->setData(channelId,       Song::ChannelIdRole);
        song->setData(channelName,     Song::ChannelNameRole);
        song->setData(channelImageUrl, Song::ChannelImageUrlRole);
        song->setData(date,            Song::BookmarkDateRole);

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
                "INSERT INTO " + _songsBookmarkTableName + " (title, artist, album, channel_id, channel_name, channel_image_url, date) \n"
                "VALUES (:title, :artist, :album, :channel_id, :channel_name, :channel_image_url, :date)"
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
                    "id                INTEGER     PRIMARY KEY,              -- bookmark id \n"
                    "title             VARCHAR(50) NOT NULL,                 -- song title \n"
                    "artist            VARCHAR(50) NOT NULL,                 -- song artist \n"
                    "album             VARCHAR(50) DEFAULT NULL,             -- song album \n"
                    "channel_id        VARCHAR(50) NOT NULL,                 -- song channel id \n"
                    "channel_name      VARCHAR(50) DEFAULT NULL,             -- song channel name \n"
                    "channel_image_url VARCHAR(80) DEFAULT NULL,             -- song channel image url \n"
                    "date              DATETIME    DEFAUT CURRENT_TIMESTAMP, -- date of bookmark creation \n"
                    "UNIQUE (title, artist) \n"
                    ")", db);

    return query.exec();
}
