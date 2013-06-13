#include "channelsproxymodel.h"

#include "channel.h"
#include "channelsmodel.h"

ChannelsProxyModel::ChannelsProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent), m_isClonesShown(false)
{
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

bool ChannelsProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    Q_UNUSED(source_parent);
    if (isClonesShown()) return true;
    QModelIndex index = sourceModel()->index(source_row, 0);
    return !sourceModel()->data(index, Channel::IsCloneRole).toBool();
}

void ChannelsProxyModel::showClones(bool show)
{
    if (show == isClonesShown()) return;
    setIsClonesShown(show);
    invalidateFilter();
}
