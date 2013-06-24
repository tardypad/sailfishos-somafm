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

bool SongsBookmarksManager::addBookmark(QString artist, QString title)
{
    if (isBookmark(artist, title)) return false;

    bookmark_t bookmark;
    bookmark.artist = artist;
    bookmark.title = title;

    m_bookmarks.append(bookmark);
    emit bookmarkAdded(artist, title);

    return true;
}

bool SongsBookmarksManager::removeBookmark(QString artist, QString title)
{
    if (!isBookmark(artist, title)) return false;

    int index = indexOf(artist, title);
    m_bookmarks.removeAt(index);
    emit bookmarkRemoved(artist, title);

    return true;
}

int SongsBookmarksManager::indexOf(QString artist, QString title)
{
    for (int row = 0; row < m_bookmarks.size(); ++row) {
        if (m_bookmarks.at(row).artist == artist
                && m_bookmarks.at(row).title == title)
            return row;
    }
    return -1;
}

QList<bookmark_t> SongsBookmarksManager::getBookmarks() const
{
    return m_bookmarks;
}

bool SongsBookmarksManager::isBookmark(QString artist, QString title) const
{
    bookmark_t bookmark;
    foreach (bookmark, m_bookmarks) {
        if (bookmark.artist == artist && bookmark.title == title)
            return true;
    }
    return false;
}
