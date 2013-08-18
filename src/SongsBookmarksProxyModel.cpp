#include "SongsBookmarksProxyModel.h"

#include <QDebug>

#include "XmlItem.h"
#include "Song.h"
#include "SongsBookmarksManager.h"

SongsBookmarksProxyModel::SongsBookmarksProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
}

void SongsBookmarksProxyModel::sortByDate()
{
    setSortRole(Song::BookmarkDateRole);
    sort(0, Qt::DescendingOrder);
}

void SongsBookmarksProxyModel::sortByChannel()
{
    setSortRole(Song::ChannelIdRole);
    sort(0, Qt::AscendingOrder);
}

XmlItem *SongsBookmarksProxyModel::itemAt(int row)
{
    SongsBookmarksManager* songsBookmarksManager = (SongsBookmarksManager*) sourceModel();
    QModelIndex sourceIndex = mapToSource(index(row, 0));

    return songsBookmarksManager->itemAt(sourceIndex.row());
}

bool SongsBookmarksProxyModel::addBookmark(XmlItem *xmlItem)
{
    SongsBookmarksManager* songsBookmarksManager = (SongsBookmarksManager*) sourceModel();
    return songsBookmarksManager->addBookmark(xmlItem);
}

bool SongsBookmarksProxyModel::removeBookmark(XmlItem *xmlItem)
{
    SongsBookmarksManager* songsBookmarksManager = (SongsBookmarksManager*) sourceModel();
    return songsBookmarksManager->removeBookmark(xmlItem);
}

bool SongsBookmarksProxyModel::isEmpty() const
{
    SongsBookmarksManager* songsBookmarksManager = (SongsBookmarksManager*) sourceModel();
    return songsBookmarksManager->isEmpty();
}
