#include "XmlItemProxyModel.h"

#include <QDebug>

#include "XmlItem.h"
#include "XmlItemModel.h"

XmlItemProxyModel::XmlItemProxyModel(QObject *parent) :
    XmlItemAbstractSortFilterProxyModel(parent), m_isClonesShown(false)
{
    connect(this, SIGNAL(sourceModelChanged()), this, SLOT(init()));
}

XmlItemModel *XmlItemProxyModel::xmlItemSourceModel()
{
    return (XmlItemModel*) sourceModel();
}

bool XmlItemProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    Q_UNUSED(source_parent);

    QModelIndex index = sourceModel()->index(source_row, 0);

    bool isClone = sourceModel()->data(index, XmlItem::IsCloneRole).toBool();
    if (!isClonesShown() && isClone)
        return false;

    bool isFavorite = sourceModel()->data(index, XmlItem::IsBookmarkRole).toBool();
    if (filterRole() == XmlItem::IsBookmarkRole && !isFavorite)
        return false;

    return true;
}

void XmlItemProxyModel::init()
{
    connect(xmlItemSourceModel(), SIGNAL(fetchStarted()), this, SIGNAL(fetchStarted()));
    connect(xmlItemSourceModel(), SIGNAL(dataFetched()), this, SIGNAL(dataFetched()));
    connect(xmlItemSourceModel(), SIGNAL(networkError()), this, SIGNAL(networkError()));
    connect(xmlItemSourceModel(), SIGNAL(parsingError()), this, SIGNAL(parsingError()));
    connect(xmlItemSourceModel(), SIGNAL(downloadProgress(qint64,qint64)), this, SIGNAL(downloadProgress(qint64,qint64)));
}

void XmlItemProxyModel::fetch()
{
    xmlItemSourceModel()->fetch();
}

void XmlItemProxyModel::abortFetching()
{
    xmlItemSourceModel()->abortFetching();
}

bool XmlItemProxyModel::hasDataBeenFetchedOnce()
{
    return xmlItemSourceModel()->hasDataBeenFetchedOnce();
}

void XmlItemProxyModel::sortByBookmarkDate()
{
    setSortRole(XmlItem::BookmarkDateRole);
    sort(0, Qt::AscendingOrder);
}

void XmlItemProxyModel::showClones(bool show)
{
    if (show == isClonesShown()) return;
    setIsClonesShown(show);
    invalidateFilter();
}

void XmlItemProxyModel::hideClones()
{
    showClones(false);
}

void XmlItemProxyModel::filterBookmarks()
{
    setFilterRole(XmlItem::IsBookmarkRole);
    invalidateFilter();
}
