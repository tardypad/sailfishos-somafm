#include "SongsBookmarksManager.h"

#include <QDebug>

#include "Song.h"
#include "SongsBookmarksDatabaseManager.h"

SongsBookmarksManager* SongsBookmarksManager::m_instance = NULL;

SongsBookmarksManager::SongsBookmarksManager(QObject *parent) :
    XmlItemBookmarkManager(new Song(), parent)
{
    m_databaseManager = SongsBookmarksDatabaseManager::instance();
    load();
}

SongsBookmarksManager* SongsBookmarksManager::instance()
{
    if (!m_instance) {
        m_instance = new SongsBookmarksManager();
    }

    return m_instance;
}

SongsBookmarksDatabaseManager *SongsBookmarksManager::songsBookmarksDatabaseManager()
{
    return (SongsBookmarksDatabaseManager*) m_databaseManager;
}

QList<QVariant> SongsBookmarksManager::channelIds()
{
    return songsBookmarksDatabaseManager()->channelIds();
}

QMap<QString, QVariant> SongsBookmarksManager::channelData(QString channelId)
{
    return songsBookmarksDatabaseManager()->channelData(channelId);
}

bool SongsBookmarksManager::removeAllChannelBookmarks(QString channelId)
{
    bool result = songsBookmarksDatabaseManager()->removeAllChannelBookmarks(channelId);

    if (!result) return false;

    deleteXmlItems(channelId, Song::ChannelIdRole);
    emit allChannelBookmarksRemoved(channelId);

    return true;
}
