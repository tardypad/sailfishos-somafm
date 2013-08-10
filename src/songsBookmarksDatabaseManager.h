#ifndef SONGSBOOKMARKSDATABASEMANAGER_H
#define SONGSBOOKMARKSDATABASEMANAGER_H

#include "xmlItemBookmarksDatabaseManager.h"

class SongsBookmarksDatabaseManager : public XmlItemBookmarksDatabaseManager
{
    Q_OBJECT

    static const QString _songsBookmarkTableName;

public:
    static SongsBookmarksDatabaseManager* instance();
    
protected:
    virtual void checkStructure();
    bool createStructure();
    
private:
    explicit SongsBookmarksDatabaseManager(QObject *parent = 0);

private:
    static SongsBookmarksDatabaseManager* m_instance;
};

#endif // SONGSBOOKMARKSDATABASEMANAGER_H
