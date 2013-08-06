#include "songsBookmarksManager.h"

#include "song.h"

SongsBookmarksManager* SongsBookmarksManager::m_instance = NULL;

SongsBookmarksManager::SongsBookmarksManager(QObject *parent) :
    XmlItemBookmarkManager(new Song(), parent)
{
}

SongsBookmarksManager* SongsBookmarksManager::instance()
{
    if (!m_instance) {
        m_instance = new SongsBookmarksManager();
    }

    return m_instance;
}
