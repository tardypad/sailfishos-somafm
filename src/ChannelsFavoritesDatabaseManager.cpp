#include "ChannelsFavoritesDatabaseManager.h"

#include <QStringList>
#include <QSqlQuery>
#include <QVariant>

#include "Channel.h"

const QString ChannelsFavoritesDatabaseManager::_channelsFavoriteTableName = "channel_favorite";

ChannelsFavoritesDatabaseManager* ChannelsFavoritesDatabaseManager::m_instance = NULL;

ChannelsFavoritesDatabaseManager::ChannelsFavoritesDatabaseManager(QObject *parent) :
    XmlItemBookmarksDatabaseManager(parent)
{
    init();
}

ChannelsFavoritesDatabaseManager* ChannelsFavoritesDatabaseManager::instance()
{
    if (!m_instance) {
        m_instance = new ChannelsFavoritesDatabaseManager;
    }

    return m_instance;
}

bool ChannelsFavoritesDatabaseManager::insertBookmark(XmlItem *xmlItem)
{
    QVariant channelId = xmlItem->data(Channel::IdRole);

    insertBookmarkPreparedQuery.bindValue(":channel_id", channelId);

    bool result = insertBookmarkPreparedQuery.exec();
    int numRowsAffected = insertBookmarkPreparedQuery.numRowsAffected();

    return result && (numRowsAffected == 1);
}

bool ChannelsFavoritesDatabaseManager::deleteBookmark(XmlItem *xmlItem)
{
    QVariant channelId = xmlItem->data(Channel::IdRole);

    deleteBookmarkPreparedQuery.bindValue(":channel_id", channelId);

    bool result = deleteBookmarkPreparedQuery.exec();
    int numRowsAffected = deleteBookmarkPreparedQuery.numRowsAffected();

    return result && (numRowsAffected >= 1);
}

void ChannelsFavoritesDatabaseManager::checkStructure()
{
    if (!db.isOpen())
        return;

    if (!db.tables().contains(_channelsFavoriteTableName)) {
        createStructure();
    }
}

void ChannelsFavoritesDatabaseManager::prepareQueries()
{
    insertBookmarkPreparedQuery.prepare(
                "INSERT INTO " + _channelsFavoriteTableName + " (channel_id) \n"
                "VALUES (:channel_id)"
                );

    deleteBookmarkPreparedQuery.prepare(
                "DELETE FROM " + _channelsFavoriteTableName + " \n"
                "WHERE channel_id=:channel_id"
                );
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
