#include "SongsBookmarksManager.h"

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
