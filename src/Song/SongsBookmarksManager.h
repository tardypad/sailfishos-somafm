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

protected:
    SongsBookmarksDatabaseManager* songsBookmarksDatabaseManager();

private:
    explicit SongsBookmarksManager(QObject *parent = 0);

private:
    static SongsBookmarksManager* m_instance;
};

#endif // SONGSBOOKMARKSMANAGER_H
