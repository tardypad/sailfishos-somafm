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
    Q_INVOKABLE bool isEmpty();
    Q_INVOKABLE void clearFilter();

protected:
    XmlItemAbstractListModel* xmlItemAbstractSourceModel();
};

#endif // XMLITEMABSTRACTSORTFILTERPROXYMODEL_H
