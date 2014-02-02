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
