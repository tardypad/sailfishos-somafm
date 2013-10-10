#include "SongsBookmarksProxyModel.h"

#include <QDebug>

#include "../XmlItem/XmlItem.h"
#include "Song.h"

SongsBookmarksProxyModel::SongsBookmarksProxyModel(QObject *parent) :
    XmlItemProxyBookmarkManager(parent)
{
}

void SongsBookmarksProxyModel::sortByChannel()
{
    setSortRole(Song::ChannelIdRole);
    sort(0, Qt::AscendingOrder);
}

