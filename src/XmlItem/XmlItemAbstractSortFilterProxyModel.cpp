/**
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

#include "XmlItemAbstractSortFilterProxyModel.h"

#include <QDebug>

#include "XmlItem.h"
#include "XmlItemAbstractListModel.h"

XmlItemAbstractSortFilterProxyModel::XmlItemAbstractSortFilterProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
}

XmlItemAbstractListModel *XmlItemAbstractSortFilterProxyModel::xmlItemAbstractSourceModel()
{
    return (XmlItemAbstractListModel*) sourceModel();
}

XmlItem *XmlItemAbstractSortFilterProxyModel::itemAt(int row)
{
    QModelIndex sourceIndex = mapToSource(index(row, 0));
    return xmlItemAbstractSourceModel()->itemAt(sourceIndex.row());
}

QMap<QString, QVariant> XmlItemAbstractSortFilterProxyModel::itemNameData(int row)
{
    QModelIndex sourceIndex = mapToSource(index(row, 0));
    return xmlItemAbstractSourceModel()->itemNameData(sourceIndex.row());
}

int XmlItemAbstractSortFilterProxyModel::rowOf(XmlItem *xmlItem)
{
    QModelIndex index = xmlItemAbstractSourceModel()->indexOf(xmlItem);
    return mapFromSource(index).row();
}

bool XmlItemAbstractSortFilterProxyModel::isEmpty()
{
    return xmlItemAbstractSourceModel()->isEmpty();
}

bool XmlItemAbstractSortFilterProxyModel::areEquals(XmlItem *xmlItem1, XmlItem *xmlItem2)
{
    return xmlItemAbstractSourceModel()->areEquals(xmlItem1, xmlItem2);
}

void XmlItemAbstractSortFilterProxyModel::clearFilter()
{
    setFilterRole(0);
    setFilterWildcard("*");
    invalidateFilter();
}
