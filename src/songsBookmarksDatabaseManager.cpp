#include "songsBookmarksDatabaseManager.h"

#include <QStringList>
#include <QSqlQuery>
#include <QVariant>

const QString SongsBookmarksDatabaseManager::_songsBookmarkTableName = "song_bookmark";

SongsBookmarksDatabaseManager* SongsBookmarksDatabaseManager::m_instance = NULL;

SongsBookmarksDatabaseManager::SongsBookmarksDatabaseManager(QObject *parent) :
    XmlItemBookmarksDatabaseManager(parent)
{
    checkStructure();
}

SongsBookmarksDatabaseManager *SongsBookmarksDatabaseManager::instance()
{
    if (!m_instance) {
        m_instance = new SongsBookmarksDatabaseManager();
    }

    return m_instance;
}

void SongsBookmarksDatabaseManager::checkStructure()
{
    if (!db.isOpen())
        return;

    if (!db.tables().contains(_songsBookmarkTableName)) {
        createStructure();
    }
}

bool SongsBookmarksDatabaseManager::createStructure()
{
    if (!db.isOpen())
        return false;

    QSqlQuery query("CREATE TABLE " + _songsBookmarkTableName + " (\n"
                    "id         INTEGER     PRIMARY KEY,              -- bookmark id \n"
                    "title      VARCHAR(50) NOT NULL,                 -- song title \n"
                    "artist     VARCHAR(50) NOT NULL,                 -- song artist \n"
                    "album      VARCHAR(50) DEFAULT NULL,             -- song album \n"
                    "channel_id VARCHAR(50) NOT NULL,                 -- song channel id \n"
                    "date       DATETIME    DEFAUT CURRENT_TIMESTAMP, -- date of bookmark creation \n"
                    "UNIQUE (title, artist) \n"
                    ")", db);

    return query.exec();
}
