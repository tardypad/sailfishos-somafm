#include "XmlItemBookmarkManager.h"

#include "XmlItem.h"

XmlItemBookmarkManager::XmlItemBookmarkManager(XmlItem *xmlItemPrototype, QObject *parent) :
    QAbstractListModel(parent),
    m_xmlItemPrototype(xmlItemPrototype),
    m_bookmarksList(QList<XmlItem*>()),
    m_databaseManager(NULL)
{
}

XmlItemBookmarkManager::~XmlItemBookmarkManager()
{
    delete m_xmlItemPrototype;
    clear();
}

void XmlItemBookmarkManager::clear()
{
    qDeleteAll(m_bookmarksList);
    m_bookmarksList.clear();
}

int XmlItemBookmarkManager::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_bookmarksList.size();
}

QHash<int,QByteArray> XmlItemBookmarkManager::roleNames() const
{
    return m_xmlItemPrototype->roleNames();
}

QVariant XmlItemBookmarkManager::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_bookmarksList.size())
        return QVariant();
    return m_bookmarksList.at(index.row())->data(role);
}

QModelIndex XmlItemBookmarkManager::indexOf(XmlItem *xmlItem) const
{
    for(int row = 0; row < m_bookmarksList.size(); ++row) {
      if (m_bookmarksList.at(row)->isEqual(xmlItem))
          return index(row);
    }
    return QModelIndex();
}

bool XmlItemBookmarkManager::addBookmark(XmlItem *xmlItem)
{
    if (isBookmark(xmlItem)) return false;

    XmlItem* newBookmark = xmlItem->clone();

    beginInsertRows(QModelIndex(), m_bookmarksList.size(), m_bookmarksList.size());
    m_bookmarksList.append(newBookmark);
    endInsertRows();

    emit bookmarkAdded(newBookmark);

    return true;
}

bool XmlItemBookmarkManager::removeBookmark(XmlItem *xmlItem)
{
    if (!isBookmark(xmlItem)) return false;

    QModelIndex index = indexOf(xmlItem);
    beginRemoveRows(QModelIndex(), index.row(), index.row());
    XmlItem* oldBookmark = m_bookmarksList.takeAt(index.row());
    endRemoveRows();

    emit bookmarkRemoved(oldBookmark);

    oldBookmark->deleteLater();

    return true;
}

bool XmlItemBookmarkManager::isBookmark(XmlItem *xmlItem) const
{
    for(int row = 0; row < m_bookmarksList.size(); ++row) {
      if (m_bookmarksList.at(row)->isEqual(xmlItem))
          return true;
    }

    return false;
}

bool XmlItemBookmarkManager::isEmpty() const
{
    return rowCount() == 0;
}

XmlItem *XmlItemBookmarkManager::itemAt(int row)
{
    if (row < 0 || row >= m_bookmarksList.size())
        return NULL;

    return m_bookmarksList.at(row);
}
