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
