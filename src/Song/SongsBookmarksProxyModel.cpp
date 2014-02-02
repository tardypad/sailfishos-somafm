/**
 *
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
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

