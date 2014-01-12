#ifndef XMLITEMPROXYBOOKMARKMANAGER_H
#define XMLITEMPROXYBOOKMARKMANAGER_H

#include "XmlItemAbstractSortFilterProxyModel.h"

class XmlItem;
class XmlItemBookmarkManager;

class XmlItemProxyBookmarkManager : public XmlItemAbstractSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit XmlItemProxyBookmarkManager(QObject *parent = 0);
    Q_INVOKABLE bool isBookmark(XmlItem* xmlItem);
    Q_INVOKABLE bool addBookmark(XmlItem* xmlItem);
    Q_INVOKABLE bool removeBookmark(XmlItem* xmlItem);
    Q_INVOKABLE bool removeAllBookmarks();
    Q_INVOKABLE void sortByDate();

protected:
    XmlItemBookmarkManager* xmlItemBookmarkSourceModel();
};

#endif // XMLITEMPROXYBOOKMARKMANAGER_H
