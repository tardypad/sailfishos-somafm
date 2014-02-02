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


#include "XmlItemBookmarkManager.h"

#include <QDebug>
#include <QDateTime>

#include "XmlItem.h"

#include "XmlItemBookmarksDatabaseManager.h"

XmlItemBookmarkManager::XmlItemBookmarkManager(XmlItem *xmlItemPrototype, QObject *parent) :
    XmlItemAbstractListModel(xmlItemPrototype, parent),
    m_databaseManager(NULL)
{
}

XmlItemBookmarkManager::~XmlItemBookmarkManager()
{
}

QHash<int,QByteArray> XmlItemBookmarkManager::roleNames() const
{
    return m_xmlItemPrototype->bookmarkRoleNames();
}

void XmlItemBookmarkManager::load()
{
    m_list = m_databaseManager->retrieveBookmarks();
}

bool XmlItemBookmarkManager::addBookmark(XmlItem *xmlItem)
{
    if (isBookmark(xmlItem)) return false;

    QDateTime currentTime = QDateTime::currentDateTime();

    XmlItem* newBookmark = xmlItem->cloneAsBookmark();
    newBookmark->setParent(this);
    newBookmark->setData(currentTime, XmlItem::BookmarkDateRole);

    bool result = m_databaseManager->insertBookmark(newBookmark);

    if (!result) return false;

    xmlItem->setData(currentTime, XmlItem::BookmarkDateRole);

    appendXmlItem(newBookmark);

    emit bookmarkAdded(newBookmark);

    return true;
}

bool XmlItemBookmarkManager::removeBookmark(XmlItem *xmlItem)
{
    if (!isBookmark(xmlItem)) return false;

    QModelIndex index = indexOf(xmlItem);
    XmlItem* oldBookmark = m_list.at(index.row());

    bool result = m_databaseManager->deleteBookmark(oldBookmark);

    if (!result) return false;

    removeXmlItemAt(index.row());

    emit bookmarkRemoved(oldBookmark);

    oldBookmark->deleteLater();

    return true;
}

bool XmlItemBookmarkManager::removeAllBookmarks()
{
    bool result = m_databaseManager->removeAllBookmarks();

    if (!result) return false;

    clear();
    emit allBookmarksRemoved();

    return true;
}

bool XmlItemBookmarkManager::isBookmark(XmlItem *xmlItem) const
{
    return contains(xmlItem);
}

QDateTime XmlItemBookmarkManager::getBookmarkDate(XmlItem *xmlItem)
{
    for(int row = 0; row < m_list.size(); ++row) {
      if (m_list.at(row)->isEqual(xmlItem))
          return m_list.at(row)->data(XmlItem::BookmarkDateRole).toDateTime();
    }

    return QDateTime();
}
