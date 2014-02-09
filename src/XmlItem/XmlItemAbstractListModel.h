/**
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
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
