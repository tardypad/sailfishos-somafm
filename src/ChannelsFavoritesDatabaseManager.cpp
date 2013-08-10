#include "ChannelsFavoritesDatabaseManager.h"

#include <QStringList>
#include <QSqlQuery>
#include <QVariant>

const QString ChannelsFavoritesDatabaseManager::_channelsFavoriteTableName = "channel_favorite";

ChannelsFavoritesDatabaseManager* ChannelsFavoritesDatabaseManager::m_instance = NULL;

ChannelsFavoritesDatabaseManager::ChannelsFavoritesDatabaseManager(QObject *parent) :
    XmlItemBookmarksDatabaseManager(parent)
{
    checkStructure();
}

ChannelsFavoritesDatabaseManager* ChannelsFavoritesDatabaseManager::instance()
{
    if (!m_instance) {
        m_instance = new ChannelsFavoritesDatabaseManager;
    }

    return m_instance;
}

void ChannelsFavoritesDatabaseManager::checkStructure()
{
    if (!db.isOpen())
        return;

    if (!db.tables().contains(_channelsFavoriteTableName)) {
        createStructure();
    }
}

bool ChannelsFavoritesDatabaseManager::createStructure()
{
    if (!db.isOpen())
        return false;

    QSqlQuery query("CREATE TABLE " + _channelsFavoriteTableName + " (\n"
                    "id         INTEGER     PRIMARY KEY,     -- favorite id \n"
                    "channel_id VARCHAR(50) UNIQUE NOT NULL  -- channel id \n"
                    ")", db);

    return query.exec();
}
