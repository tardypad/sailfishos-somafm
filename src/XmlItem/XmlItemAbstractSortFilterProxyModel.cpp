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

bool XmlItemAbstractSortFilterProxyModel::isEmpty()
{
    return xmlItemAbstractSourceModel()->isEmpty();
}

void XmlItemAbstractSortFilterProxyModel::clearFilter()
{
    setFilterRole(0);
    setFilterWildcard("*");
    invalidateFilter();
}
