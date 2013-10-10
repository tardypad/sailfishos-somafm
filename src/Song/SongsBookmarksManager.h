#ifndef SONGSBOOKMARKSMANAGER_H
#define SONGSBOOKMARKSMANAGER_H

#include "../XmlItem/XmlItemBookmarkManager.h"

class SongsBookmarksManager : public XmlItemBookmarkManager
{
    Q_OBJECT
public:
    static SongsBookmarksManager* instance();

private:
    explicit SongsBookmarksManager(QObject *parent = 0);

private:
    static SongsBookmarksManager* m_instance;
};

#endif // SONGSBOOKMARKSMANAGER_H
