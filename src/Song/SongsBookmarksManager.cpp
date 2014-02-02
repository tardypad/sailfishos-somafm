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


#include "SongsBookmarksManager.h"

#include <QDebug>

#include "Song.h"
#include "SongsBookmarksDatabaseManager.h"

SongsBookmarksManager* SongsBookmarksManager::m_instance = NULL;

SongsBookmarksManager::SongsBookmarksManager(QObject *parent) :
    XmlItemBookmarkManager(new Song(), parent)
{
    m_databaseManager = SongsBookmarksDatabaseManager::instance();
    load();

    connect(this, SIGNAL(bookmarkAdded(XmlItem*)), this, SLOT(checkFirstChannelBookmark(XmlItem*)));
}

SongsBookmarksManager* SongsBookmarksManager::instance()
{
    if (!m_instance) {
        m_instance = new SongsBookmarksManager();
    }

    return m_instance;
}

SongsBookmarksDatabaseManager *SongsBookmarksManager::songsBookmarksDatabaseManager()
{
    return (SongsBookmarksDatabaseManager*) m_databaseManager;
}

void SongsBookmarksManager::checkFirstChannelBookmark(XmlItem *xmlItem)
{
    QString channelId = xmlItem->data(Song::ChannelIdRole).toString();
    int count = songsBookmarksDatabaseManager()->channelCount(channelId);

    if (count == 1) {
        emit firstChannelBookmark(channelId);
    }
}

QList<QVariant> SongsBookmarksManager::channelIds()
{
    return songsBookmarksDatabaseManager()->channelIds();
}

QMap<QString, QVariant> SongsBookmarksManager::channelData(QString channelId)
{
    return songsBookmarksDatabaseManager()->channelData(channelId);
}

bool SongsBookmarksManager::removeAllChannelBookmarks(QString channelId)
{
    bool result = songsBookmarksDatabaseManager()->removeAllChannelBookmarks(channelId);

    if (!result) return false;

    deleteXmlItems(channelId, Song::ChannelIdRole);
    emit allChannelBookmarksRemoved(channelId);

    return true;
}
