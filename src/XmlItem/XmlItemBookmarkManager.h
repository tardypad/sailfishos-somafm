/**
 * Copyright (c) 2013-2019 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

#ifndef XMLITEMBOOKMARKMANAGER_H
#define XMLITEMBOOKMARKMANAGER_H

#include "XmlItemAbstractListModel.h"

class XmlItemBookmarksDatabaseManager;

class XmlItemBookmarkManager : public XmlItemAbstractListModel
{
    Q_OBJECT
public:
    ~XmlItemBookmarkManager();
    virtual QHash<int,QByteArray> roleNames() const;
    bool addBookmark(XmlItem* xmlItem);
    bool removeBookmark(XmlItem* xmlItem);
    bool removeAllBookmarks();
    bool isBookmark(XmlItem* xmlItem) const;
    QDateTime getBookmarkDate(XmlItem* xmlItem);

protected:
    explicit XmlItemBookmarkManager(XmlItem* xmlItemPrototype, QObject *parent = 0);
    void load();

signals:
    void bookmarkAdded(XmlItem* xmlItem);
    void bookmarkRemoved(XmlItem* xmlItem);
    void allBookmarksRemoved();

protected:
    XmlItemBookmarksDatabaseManager* m_databaseManager;
};

#endif // XMLITEMBOOKMARKMANAGER_H
