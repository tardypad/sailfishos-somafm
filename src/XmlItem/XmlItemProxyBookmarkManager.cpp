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
