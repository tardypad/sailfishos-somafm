/**
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

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

void SongsBookmarksProxyModel::init()
{
    XmlItemProxyBookmarkManager::init();
    connect(songBookmarksManagerSourceModel(), SIGNAL(firstChannelBookmark(QString)), this, SIGNAL(firstChannelBookmark(QString)));
    connect(songBookmarksManagerSourceModel(), SIGNAL(allChannelBookmarksRemoved(QString)), this, SIGNAL(allChannelBookmarksRemoved(QString)));
}

bool SongsBookmarksProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    if (sortRole() != Song::ChannelIdRole)
        return XmlItemProxyBookmarkManager::lessThan(left, right);

    QString leftChannelName = sourceModel()->data(left, Song::ChannelNameRole).toString();
    QString rightChannelName = sourceModel()->data(right, Song::ChannelNameRole).toString();

    if (leftChannelName < rightChannelName) return true;

    if (leftChannelName > rightChannelName) return false;

    QDateTime leftDate= sourceModel()->data(left, Song::BookmarkDateRole).toDateTime();
    QDateTime rightDate = sourceModel()->data(right, Song::BookmarkDateRole).toDateTime();

    if (leftDate > rightDate) return true;

    return false;
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

bool SongsBookmarksProxyModel::removeAllChannelBookmarks(QString channelId)
{
    return songBookmarksManagerSourceModel()->removeAllChannelBookmarks(channelId);
}

