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

bool XmlItemProxyBookmarkManager::isBookmark(XmlItem *xmlItem)
{
    return xmlItemBookmarkSourceModel()->isBookmark(xmlItem);
}

bool XmlItemProxyBookmarkManager::addBookmark(XmlItem *xmlItem)
{
    return xmlItemBookmarkSourceModel()->addBookmark(xmlItem);
}

bool XmlItemProxyBookmarkManager::removeBookmark(XmlItem *xmlItem)
{
    return xmlItemBookmarkSourceModel()->removeBookmark(xmlItem);
}

bool XmlItemProxyBookmarkManager::removeAllBookmarks()
{
    return xmlItemBookmarkSourceModel()->removeAllBookmarks();
}

void XmlItemProxyBookmarkManager::sortByDate()
{
    setSortRole(XmlItem::BookmarkDateRole);
    sort(0, Qt::DescendingOrder);
}
