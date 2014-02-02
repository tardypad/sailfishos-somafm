/**
 *
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 **/


#include "ChannelsFavoritesDatabaseManager.h"

#include <QDebug>
#include <QStringList>
#include <QSqlQuery>
#include <QVariant>
#include <QDateTime>

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
        m_instance = new ChannelsFavoritesDatabaseManager();
    }

    return m_instance;
}

bool ChannelsFavoritesDatabaseManager::insertBookmark(XmlItem *xmlItem)
{
    QVariant channelId = xmlItem->data(Channel::IdRole);
    QVariant name = xmlItem->data(Channel::NameRole);

    insertBookmarkPreparedQuery.bindValue(":channel_id", channelId);
    insertBookmarkPreparedQuery.bindValue(":name", name);
    insertBookmarkPreparedQuery.bindValue(":date", QDateTime::currentDateTime());

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

bool ChannelsFavoritesDatabaseManager::removeAllBookmarks()
{
    QSqlQuery query("DELETE FROM " + _channelsFavoriteTableName);
    return query.exec();
}

QList<XmlItem *> ChannelsFavoritesDatabaseManager::retrieveBookmarks()
{
    QList<XmlItem *> xmlItemsBookmarks;
    QSqlQuery query("SELECT channel_id, name, date FROM " + _channelsFavoriteTableName);
    QVariant channelId, name, date;

    while (query.next()) {
        channelId = query.value(0);
        name = query.value(1);
        date = query.value(2);

        Channel* channel = new Channel(this);
        channel->setData(channelId, Channel::IdRole);
        channel->setData(name, Channel::NameRole);
        channel->setData(date, Channel::BookmarkDateRole);

        xmlItemsBookmarks.append(channel);
    }

    return xmlItemsBookmarks;
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
                "INSERT INTO " + _channelsFavoriteTableName + " (channel_id, name, date) \n"
                "VALUES (:channel_id, :name, :date)"
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
                    "id         INTEGER     PRIMARY KEY,             -- favorite id \n"
                    "channel_id VARCHAR(50) UNIQUE NOT NULL,         -- channel id \n"
                    "name       VARCHAR(50) NOT NULL,                -- channel name \n"
                    "date       DATETIME    DEFAUT CURRENT_TIMESTAMP -- date of bookmark creation \n"
                    ")", db);

    return query.exec();
}
