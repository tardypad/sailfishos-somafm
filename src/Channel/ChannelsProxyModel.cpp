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

QList<QVariant> ChannelsProxyModel::streamsQualities()
{
    QList<QVariant> qualities;
    for (int q = Channel::FirstQuality; q <= Channel::LastQuality; ++q) {
        qualities.append(Channel::streamQualityText( (Channel::StreamQuality) q ));
    }
    return qualities;
}

QList<QVariant> ChannelsProxyModel::streamsFormats()
{
    QList<QVariant> formats;
    for (int f = Channel::FirstFormat; f <= Channel::LastFormat; ++f) {
        formats.append(Channel::streamFormatText( (Channel::StreamFormat) f ));
    }
    return formats;
}

