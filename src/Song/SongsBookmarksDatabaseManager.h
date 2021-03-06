/**
 * Copyright (c) 2013-2019 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

#ifndef SONGSBOOKMARKSDATABASEMANAGER_H
#define SONGSBOOKMARKSDATABASEMANAGER_H

#include "../XmlItem/XmlItemBookmarksDatabaseManager.h"

class SongsBookmarksDatabaseManager : public XmlItemBookmarksDatabaseManager
{
    Q_OBJECT

    static const QString _songsBookmarkTableName;

public:
    static SongsBookmarksDatabaseManager* instance();
    virtual bool insertBookmark(XmlItem *xmlItem);
    virtual bool deleteBookmark(XmlItem *xmlItem);
    virtual bool removeAllBookmarks();
    bool removeAllChannelBookmarks(QString channelId);
    virtual QList<XmlItem*> retrieveBookmarks();
    QList<QVariant> channelIds();
    QMap<QString, QVariant> channelData(QString channelId);
    int channelCount(QString channelId);
    
protected:
    virtual void checkStructure();
    virtual void prepareQueries();
    bool createStructure();
    
private:
    explicit SongsBookmarksDatabaseManager(QObject *parent = 0);

private:
    static SongsBookmarksDatabaseManager* m_instance;
};

#endif // SONGSBOOKMARKSDATABASEMANAGER_H
