/**
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

#ifndef XMLITEMABSTRACTSORTFILTERPROXYMODEL_H
#define XMLITEMABSTRACTSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

#include "XmlItemAbstractListModel.h"

class XmlItem;
class XmlItemAbstractListModel;

class XmlItemAbstractSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit XmlItemAbstractSortFilterProxyModel(QObject *parent = 0);
    Q_INVOKABLE XmlItem* itemAt(int row);
    Q_INVOKABLE QMap<QString, QVariant> itemNameData(int row);
    Q_INVOKABLE int rowOf(XmlItem* xmlItem);
    Q_INVOKABLE bool isEmpty();
    Q_INVOKABLE bool areEquals(XmlItem* xmlItem1, XmlItem* xmlItem2);
    Q_INVOKABLE void clearFilter();

protected:
    XmlItemAbstractListModel* xmlItemAbstractSourceModel();
};

#endif // XMLITEMABSTRACTSORTFILTERPROXYMODEL_H
