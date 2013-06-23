#include "bookmarksManager.h"

BookmarksManager* BookmarksManager::m_instance = NULL;

BookmarksManager::BookmarksManager(QObject *parent) :
    QObject(parent), m_bookmarks(QList<bookmark_t>())
{
}

BookmarksManager* BookmarksManager::instance()
{
    if (!m_instance) {
        m_instance = new BookmarksManager();
    }

    return m_instance;
}

bool BookmarksManager::addBookmark(QString artist, QString title)
{
    if (isBookmark(artist, title)) return false;

    bookmark_t bookmark;
    bookmark.artist = artist;
    bookmark.title = title;

    m_bookmarks.append(bookmark);
    emit bookmarkAdded(artist, title);

    return true;
}

bool BookmarksManager::removeBookmark(QString artist, QString title)
{
    if (!isBookmark(artist, title)) return false;

    int index = indexOf(artist, title);
    m_bookmarks.removeAt(index);
    emit bookmarkRemoved(artist, title);

    return true;
}

int BookmarksManager::indexOf(QString artist, QString title)
{
    for (int row = 0; row < m_bookmarks.size(); ++row) {
        if (m_bookmarks.at(row).artist == artist
                && m_bookmarks.at(row).title == title)
            return row;
    }
    return -1;
}

QList<bookmark_t> BookmarksManager::getBookmarks() const
{
    return m_bookmarks;
}

bool BookmarksManager::isBookmark(QString artist, QString title) const
{
    bookmark_t bookmark;
    foreach (bookmark, m_bookmarks) {
        if (bookmark.artist == artist && bookmark.title == title)
            return true;
    }
    return false;
}
