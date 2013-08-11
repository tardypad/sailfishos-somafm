#ifndef SONGSBOOKMARKSDATABASEMANAGER_H
#define SONGSBOOKMARKSDATABASEMANAGER_H

#include "XmlItemBookmarksDatabaseManager.h"

class SongsBookmarksDatabaseManager : public XmlItemBookmarksDatabaseManager
{
    Q_OBJECT

    static const QString _songsBookmarkTableName;

public:
    static SongsBookmarksDatabaseManager* instance();
    virtual bool insertBookmark(XmlItem *xmlItem);
    virtual bool deleteBookmark(XmlItem *xmlItem);
    
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
