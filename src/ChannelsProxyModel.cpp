#include "ChannelsProxyModel.h"

#include <QDebug>

#include "Channel.h"
#include "ChannelsModel.h"
#include "XmlItem.h"

ChannelsProxyModel::ChannelsProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent), m_isClonesShown(false)
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

bool ChannelsProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    Q_UNUSED(source_parent);

    QModelIndex index = sourceModel()->index(source_row, 0);

    bool isClone = sourceModel()->data(index, Channel::IsCloneRole).toBool();
    if (!isClonesShown() && isClone)
        return false;

    bool isFavorite = sourceModel()->data(index, Channel::IsBookmarkRole).toBool();
    if (filterRole() == Channel::IsBookmarkRole && !isFavorite)
        return false;

    return true;
}

void ChannelsProxyModel::clearFilter()
{
    setFilterRole(0);
    invalidateFilter();
}

void ChannelsProxyModel::showClones(bool show)
{
    if (show == isClonesShown()) return;
    setIsClonesShown(show);
    invalidateFilter();
}

void ChannelsProxyModel::hideClones()
{
    showClones(false);
}

void ChannelsProxyModel::filterFavorites()
{
    setFilterRole(Channel::IsBookmarkRole);
    invalidateFilter();
}

XmlItem* ChannelsProxyModel::itemAt(int row)
{
    ChannelsModel* channelsModel = (ChannelsModel*) sourceModel();
    QModelIndex sourceIndex = mapToSource(index(row, 0));

    return channelsModel->itemAt(sourceIndex.row());
}
