#include "SongsBookmarksProxyModel.h"

#include <QDebug>

#include "../XmlItem/XmlItem.h"
#include "Song.h"
#include "SongsBookmarksManager.h"

SongsBookmarksProxyModel::SongsBookmarksProxyModel(QObject *parent) :
    XmlItemProxyBookmarkManager(parent)
{
}

SongsBookmarksManager *SongsBookmarksProxyModel::songBookmarksManagerSourceModel()
{
    return (SongsBookmarksManager*) sourceModel();
}

void SongsBookmarksProxyModel::filterByChannel(QString channelId)
{
    setFilterRole(Song::ChannelIdRole);
    setFilterFixedString(channelId);
    invalidateFilter();
}

void SongsBookmarksProxyModel::sortByChannel()
{
    setSortRole(Song::ChannelIdRole);
    sort(0, Qt::AscendingOrder);
}

QList<QVariant> SongsBookmarksProxyModel::channelIds()
{
    return songBookmarksManagerSourceModel()->channelIds();
}

QMap<QString, QVariant> SongsBookmarksProxyModel::channelData(QString channelId)
{
    return songBookmarksManagerSourceModel()->channelData(channelId);
}

