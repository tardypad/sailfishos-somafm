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
