/**
 * Copyright (c) 2013-2019 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

#ifndef CHANNELSFAVORITESDATABASEMANAGER_H
#define CHANNELSFAVORITESDATABASEMANAGER_H

#include "../XmlItem/XmlItemBookmarksDatabaseManager.h"

class ChannelsFavoritesDatabaseManager : public XmlItemBookmarksDatabaseManager
{
    Q_OBJECT

    static const QString _channelsFavoriteTableName;

public:
    static ChannelsFavoritesDatabaseManager* instance();
    virtual bool insertBookmark(XmlItem *xmlItem);
    virtual bool deleteBookmark(XmlItem *xmlItem);
    virtual bool removeAllBookmarks();
    virtual QList<XmlItem*> retrieveBookmarks();
    
protected:
    virtual void checkStructure();
    virtual void prepareQueries();
    bool createStructure();

private:
    explicit ChannelsFavoritesDatabaseManager(QObject *parent = 0);

private:
    static ChannelsFavoritesDatabaseManager* m_instance;
};

#endif // CHANNELSFAVORITESDATABASEMANAGER_H
