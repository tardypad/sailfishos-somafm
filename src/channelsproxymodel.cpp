#include "channelsproxymodel.h"

#include "channel.h"

ChannelsProxyModel::ChannelsProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
}

void ChannelsProxyModel::sortByListeners()
{
    setSortRole(Channel::ListenersRole);
    sort(0, Qt::DescendingOrder);
}
