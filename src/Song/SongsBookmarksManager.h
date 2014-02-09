/**
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

#ifndef SONGSBOOKMARKSMANAGER_H
#define SONGSBOOKMARKSMANAGER_H

#include "../XmlItem/XmlItemBookmarkManager.h"

class SongsBookmarksDatabaseManager;

class SongsBookmarksManager : public XmlItemBookmarkManager
{
    Q_OBJECT
public:
    static SongsBookmarksManager* instance();
    QList<QVariant> channelIds();
    QMap<QString, QVariant> channelData(QString channelId);
    bool removeAllChannelBookmarks(QString channelId);

signals:
    void allChannelBookmarksRemoved(QString channelId);
    void firstChannelBookmark(QString channelId);

protected:
    SongsBookmarksDatabaseManager* songsBookmarksDatabaseManager();

private slots:
    void checkFirstChannelBookmark(XmlItem* xmlItem);

private:
    explicit SongsBookmarksManager(QObject *parent = 0);

private:
    static SongsBookmarksManager* m_instance;
};

#endif // SONGSBOOKMARKSMANAGER_H
