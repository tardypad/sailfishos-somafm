#include "songsBookmarksManager.h"

SongsBookmarksManager* SongsBookmarksManager::m_instance = NULL;

SongsBookmarksManager::SongsBookmarksManager(QObject *parent) :
    QObject(parent), m_bookmarks(QList<bookmark_t>())
{
}

SongsBookmarksManager* SongsBookmarksManager::instance()
{
    if (!m_instance) {
        m_instance = new SongsBookmarksManager();
    }

    return m_instance;
}

bool SongsBookmarksManager::addBookmark(QString channelId, QString artist, QString title)
{
    if (isBookmark(channelId, artist, title)) return false;

    bookmark_t bookmark;
    bookmark.channelId = channelId;
    bookmark.artist = artist;
    bookmark.title = title;

    m_bookmarks.append(bookmark);
    emit bookmarkAdded(channelId, artist, title);

    return true;
}

bool SongsBookmarksManager::removeBookmark(QString channelId, QString artist, QString title)
{
    if (!isBookmark(channelId, artist, title)) return false;

    int index = indexOf(channelId, artist, title);
    m_bookmarks.removeAt(index);
    emit bookmarkRemoved(channelId, artist, title);

    return true;
}

int SongsBookmarksManager::indexOf(QString channelId, QString artist, QString title)
{
    for (int row = 0; row < m_bookmarks.size(); ++row) {
        if (m_bookmarks.at(row).channelId == channelId
                && m_bookmarks.at(row).artist == artist
                && m_bookmarks.at(row).title == title)
            return row;
    }
    return -1;
}

QList<bookmark_t> SongsBookmarksManager::getBookmarks() const
{
    return m_bookmarks;
}

bool SongsBookmarksManager::isBookmark(QString channelId, QString artist, QString title) const
{
    bookmark_t bookmark;
    foreach (bookmark, m_bookmarks) {
        if (bookmark.channelId == channelId
                &&bookmark.artist == artist
                && bookmark.title == title)
            return true;
    }
    return false;
}
