/**
 * Copyright (c) 2013-2019 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

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

signals:
    void bookmarkAdded(XmlItem* xmlItem);
    void bookmarkRemoved(XmlItem* xmlItem);
    void allBookmarksRemoved();

protected slots:
    virtual void init();

protected:
    XmlItemBookmarkManager* xmlItemBookmarkSourceModel();
};

#endif // XMLITEMPROXYBOOKMARKMANAGER_H
