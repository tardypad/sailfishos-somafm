/**
 * Copyright (c) 2013-2019 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

#include "XmlItemProxyBookmarkManager.h"

#include <QDebug>

#include "XmlItem.h"
#include "XmlItemBookmarkManager.h"

XmlItemProxyBookmarkManager::XmlItemProxyBookmarkManager(QObject *parent) :
    XmlItemAbstractSortFilterProxyModel(parent)
{
    connect(this, SIGNAL(sourceModelChanged()), this, SLOT(init()));
}

XmlItemBookmarkManager *XmlItemProxyBookmarkManager::xmlItemBookmarkSourceModel()
{
    return (XmlItemBookmarkManager*) sourceModel();
}

void XmlItemProxyBookmarkManager::init()
{
    connect(xmlItemBookmarkSourceModel(), SIGNAL(bookmarkAdded(XmlItem*)), this, SIGNAL(bookmarkAdded(XmlItem*)));
    connect(xmlItemBookmarkSourceModel(), SIGNAL(bookmarkRemoved(XmlItem*)), this, SIGNAL(bookmarkRemoved(XmlItem*)));
    connect(xmlItemBookmarkSourceModel(), SIGNAL(allBookmarksRemoved()), this, SIGNAL(allBookmarksRemoved()));
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
