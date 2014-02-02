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


#include "ChannelsProxyModel.h"

#include <QDebug>

#include "../XmlItem/XmlItem.h"
#include "Channel.h"
#include "ChannelsModel.h"

ChannelsProxyModel::ChannelsProxyModel(QObject *parent) :
    XmlItemProxyModel(parent)
{
    setSortCaseSensitivity(Qt::CaseInsensitive);
}

ChannelsModel *ChannelsProxyModel::channelsSourceModel()
{
    return (ChannelsModel*) sourceModel();
}

bool ChannelsProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    if (sortRole() != Channel::SortGenreRole)
        return XmlItemProxyModel::lessThan(left, right);

    QString leftGenre = sourceModel()->data(left, Channel::SortGenreRole).toString();
    QString rightGenre = sourceModel()->data(right, Channel::SortGenreRole).toString();

    if (leftGenre < rightGenre) return true;

    if (leftGenre > rightGenre) return false;

    QString leftName = sourceModel()->data(left, Channel::NameRole).toString();
    QString rightName = sourceModel()->data(right, Channel::NameRole).toString();

    if (leftName < rightName) return true;

    return false;
}

void ChannelsProxyModel::sortByListeners()
{
    setSortRole(Channel::ListenersRole);
    sort(0, Qt::DescendingOrder);
}

void ChannelsProxyModel::sortByGenres()
{
    setSortRole(Channel::SortGenreRole);
    sort(0, Qt::AscendingOrder);
}

void ChannelsProxyModel::sortByName()
{
    setSortRole(Channel::NameRole);
    sort(0, Qt::AscendingOrder);
}

void ChannelsProxyModel::filterFavorites()
{
    filterBookmarks();
}

Channel *ChannelsProxyModel::channelItem(QString channelId)
{
    return channelsSourceModel()->channelItem(channelId);
}

QMap<QString, QVariant> ChannelsProxyModel::channelItemNameData(QString channelId)
{
    return channelsSourceModel()->channelItemNameData(channelId);
}

QList<QString> ChannelsProxyModel::streamsQualities()
{
    return Channel::streamQualityTextList();
}

QList<QString> ChannelsProxyModel::streamsFormats()
{
    return Channel::streamFormatTextList();
}

QMap<QString, QVariant> ChannelsProxyModel::channelStreams(QString channelId)
{
    QMap<QString, QVariant> streams = channelsSourceModel()->channelStreams(channelId);

    // QVariantList on QML side doesn't support multiple keys
    QMap<QString, QVariant> result;

    QMapIterator<QString, QVariant> iterator(streams);
    int i = 0;
    while (iterator.hasNext()) {
        i++;
        iterator.next();
        result.insert(iterator.key() + QString::number(i), iterator.value());
    }

    return result;
}

