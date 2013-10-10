#include "XmlItemProxyBookmarkManager.h"

#include <QDebug>

#include "XmlItem.h"
#include "XmlItemBookmarkManager.h"

XmlItemProxyBookmarkManager::XmlItemProxyBookmarkManager(QObject *parent) :
    XmlItemAbstractSortFilterProxyModel(parent)
{
}

XmlItemBookmarkManager *XmlItemProxyBookmarkManager::xmlItemBookmarkSourceModel()
{
    return (XmlItemBookmarkManager*) sourceModel();
}

bool XmlItemProxyBookmarkManager::addBookmark(XmlItem *xmlItem)
{
    return xmlItemBookmarkSourceModel()->addBookmark(xmlItem);
}

bool XmlItemProxyBookmarkManager::removeBookmark(XmlItem *xmlItem)
{
    return xmlItemBookmarkSourceModel()->removeBookmark(xmlItem);
}

void XmlItemProxyBookmarkManager::sortByDate()
{
    setSortRole(XmlItem::BookmarkDateRole);
    sort(0, Qt::DescendingOrder);
}