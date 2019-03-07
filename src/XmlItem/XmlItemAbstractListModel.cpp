/**
 * Copyright (c) 2013-2019 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

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

void XmlItemAbstractListModel::preprendXmlItem(XmlItem *xmlItem)
{
    beginInsertRows(QModelIndex(), 0, 0);
    m_list.prepend(xmlItem);
    endInsertRows();
}

void XmlItemAbstractListModel::appendXmlItems(QList<XmlItem *> xmlItemsList)
{
    beginInsertRows(QModelIndex(), m_list.size(), m_list.size() + xmlItemsList.size() - 1);
    m_list.append(xmlItemsList);
    endInsertRows();
}

void XmlItemAbstractListModel::removeXmlItemAt(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    m_list.removeAt(row);
    endRemoveRows();
}

void XmlItemAbstractListModel::deleteXmlItems(const QVariant &value, int role)
{
    QMutableListIterator<XmlItem*> iterator(m_list);
    XmlItem* xmlItem;
    beginResetModel();
    while (iterator.hasNext()) {
        xmlItem = iterator.next();
        if (xmlItem->data(role) == value) {
            iterator.remove();
            delete xmlItem;
        }
    }
    endResetModel();
}

XmlItem* XmlItemAbstractListModel::itemAt(int row)
{
    if (row < 0 || row >= m_list.size())
        return NULL;

    return m_list.at(row);
}

bool XmlItemAbstractListModel::areEquals(XmlItem *xmlItem1, XmlItem *xmlItem2)
{
    return xmlItem1->isEqual(xmlItem2);
}

QMap<QString, QVariant> XmlItemAbstractListModel::itemNameData(int row)
{
    QMap<QString, QVariant> result;

    QHash<int, QByteArray> roleNames = m_xmlItemPrototype->roleNames();

    QHashIterator<int, QByteArray> iterator(roleNames);
    QVariant itemValue;
    QString roleName;
    int roleInt;

    while (iterator.hasNext()) {
        iterator.next();
        roleInt = iterator.key();
        roleName = QString(iterator.value());
        itemValue = data(index(row), roleInt);
        result.insert(roleName, itemValue);
    }

    return result;
}

QModelIndex XmlItemAbstractListModel::indexOf(XmlItem *xmlItem) const
{
    for(int row = 0; row < m_list.size(); ++row) {
      if (m_list.at(row)->isEqual(xmlItem))
          return index(row);
    }
    return QModelIndex();
}

void XmlItemAbstractListModel::setDataItem(XmlItem *xmlItem, const QVariant &value, int role, bool exclusive, const QVariant &value2)
{
    for (int row = 0; row < m_list.size(); ++row) {
        if (m_list.at(row)->isEqual(xmlItem)) {
            setData(index(row) ,value, role);
        } else if (!exclusive) {
            setData(index(row) ,value2, role);
        }
    }
}

void XmlItemAbstractListModel::setDataItems(const QVariant &checkValue, int checkRole, const QVariant &value, int role)
{
    for (int row = 0; row < m_list.size(); ++row) {
        if (m_list.at(row)->data(checkRole) == checkValue) {
            setData(index(row) ,value, role);
        }
    }
}

void XmlItemAbstractListModel::setDataAll(const QVariant &value, int role)
{
    for (int row = 0; row < m_list.size(); ++row) {
        setData(index(row) ,value, role);
    }
}
