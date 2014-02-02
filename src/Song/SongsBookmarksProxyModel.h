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


#ifndef SONGSBOOKMARKSPROXYMODEL_H
#define SONGSBOOKMARKSPROXYMODEL_H

#include "../XmlItem/XmlItemProxyBookmarkManager.h"

class XmlItem;
class SongsBookmarksManager;

class SongsBookmarksProxyModel : public XmlItemProxyBookmarkManager
{
    Q_OBJECT
public:
    explicit SongsBookmarksProxyModel(QObject *parent = 0);
    virtual bool lessThan(const QModelIndex &left, const QModelIndex &right) const;
    Q_INVOKABLE void filterByChannel(QString channelId);
    Q_INVOKABLE void sortByChannel();
    Q_INVOKABLE QList<QVariant> channelIds();
    Q_INVOKABLE QMap<QString, QVariant> channelData(QString channelId);
    Q_INVOKABLE bool removeAllChannelBookmarks(QString channelId);

signals:
    void allChannelBookmarksRemoved(QString channelId);
    void firstChannelBookmark(QString channelId);

protected slots:
    virtual void init();

protected:
    SongsBookmarksManager* songBookmarksManagerSourceModel();
};

#endif // SONGSBOOKMARKSPROXYMODEL_H
