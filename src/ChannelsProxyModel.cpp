#include "ChannelsProxyModel.h"

#include <QDebug>

#include "XmlItem.h"
#include "Channel.h"

ChannelsProxyModel::ChannelsProxyModel(QObject *parent) :
    XmlItemProxyModel(parent)
{
    setSortCaseSensitivity(Qt::CaseInsensitive);
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

