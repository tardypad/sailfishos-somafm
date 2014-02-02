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


#ifndef XMLITEMABSTRACTLISTMODEL_H
#define XMLITEMABSTRACTLISTMODEL_H

#include <QAbstractListModel>

class XmlItem;

class XmlItemAbstractListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit XmlItemAbstractListModel(XmlItem* xmlItemPrototype, QObject *parent = 0);
    ~XmlItemAbstractListModel();
    virtual QHash<int,QByteArray> roleNames() const = 0;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual bool setData (const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    bool contains(XmlItem* xmlItem) const;
    Q_INVOKABLE bool isEmpty() const;
    Q_INVOKABLE XmlItem* itemAt(int row);
    bool areEquals(XmlItem* xmlItem1, XmlItem* xmlItem2);
    QMap<QString, QVariant> itemNameData(int row);
    QModelIndex indexOf(XmlItem* xmlItem) const;
    
protected:
    void clear();
    void appendXmlItem(XmlItem* xmlItem);
    void preprendXmlItem(XmlItem* xmlItem);
    void appendXmlItems(QList<XmlItem*> xmlItemsList);
    void removeXmlItemAt(int row);
    void deleteXmlItems(const QVariant &value, int role);
    void setDataItem(XmlItem* xmlItem, const QVariant &value, int role, bool exclusive = true, const QVariant &value2 = false);
    void setDataItems(const QVariant &checkValue, int checkRole, const QVariant &value, int role);
    void setDataAll(const QVariant &value, int role);

protected:
    QList<XmlItem*> m_list;
    XmlItem* m_xmlItemPrototype;
};

#endif // XMLITEMABSTRACTLISTMODEL_H
