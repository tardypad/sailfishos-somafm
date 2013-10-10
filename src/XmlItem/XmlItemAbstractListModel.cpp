#include "XmlItemAbstractListModel.h"

#include <QDebug>

#include "XmlItem.h"

XmlItemAbstractListModel::XmlItemAbstractListModel(XmlItem* xmlItemPrototype, QObject *parent) :
    QAbstractListModel(parent),
    m_list(QList<XmlItem*>()),
  m_xmlItemPrototype(xmlItemPrototype)

{
}

XmlItemAbstractListModel::~XmlItemAbstractListModel()
{
    delete m_xmlItemPrototype;
    clear();
}

int XmlItemAbstractListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_list.size();
}

void XmlItemAbstractListModel::clear()
{
    beginResetModel();
    qDeleteAll(m_list);
    m_list.clear();
    endResetModel();
}

QVariant XmlItemAbstractListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_list.size())
        return QVariant();
    return m_list.at(index.row())->data(role);
}

bool XmlItemAbstractListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() < 0 || index.row() >= m_list.size())
        return false;

    bool result = m_list.at(index.row())->setData(value, role);

    if (result)
        emit dataChanged(index, index);

    return result;
}

bool XmlItemAbstractListModel::contains(XmlItem *xmlItem) const
{
    for(int row = 0; row < m_list.size(); ++row) {
      if (m_list.at(row)->isEqual(xmlItem))
          return true;
    }

    return false;
}

bool XmlItemAbstractListModel::isEmpty() const
{
    return rowCount() == 0;
}

void XmlItemAbstractListModel::appendXmlItem(XmlItem *xmlItem)
{
    beginInsertRows(QModelIndex(), m_list.size(), m_list.size());
    m_list.append(xmlItem);
    endInsertRows();
}

void XmlItemAbstractListModel::removeXmlItemAt(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    m_list.removeAt(row);
    endRemoveRows();
}

XmlItem* XmlItemAbstractListModel::itemAt(int row)
{
    if (row < 0 || row >= m_list.size())
        return NULL;

    return m_list.at(row);
}

QModelIndex XmlItemAbstractListModel::indexOf(XmlItem *xmlItem) const
{
    for(int row = 0; row < m_list.size(); ++row) {
      if (m_list.at(row)->isEqual(xmlItem))
          return index(row);
    }
    return QModelIndex();
}

void XmlItemAbstractListModel::setDataItem(XmlItem *xmlItem, const QVariant &value, int role)
{
    for (int row = 0; row < m_list.size(); ++row) {
        if (m_list.at(row)->isEqual(xmlItem)) {
            setData(index(row) ,value, role);
        }
    }
}
