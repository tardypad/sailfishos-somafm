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
