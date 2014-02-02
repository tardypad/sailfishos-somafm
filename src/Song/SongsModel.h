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


#ifndef SONGSMODEL_H
#define SONGSMODEL_H

#include "../XmlItem/XmlItemModel.h"

class Song;
class Channel;
class RefreshModel;

class SongsModel : public XmlItemModel
{
    static const QUrl _channelSongsUrl;

    Q_OBJECT
public:
    explicit SongsModel(QObject *parent = 0);
    ~SongsModel();
    void setChannel(XmlItem* channel);
    void fetchAdditional();

signals:
    void fetchUpdateStarted();
    void fetchUpdateFinished();

private slots:
    void parseAdditional();
    void removeAllFromChannelBookmarks(QString channelId);
    void updateCurrentSong();

private:
    virtual bool includeXmlItem(XmlItem *xmlItem);
    virtual XmlItem* parseXmlItem();

private:
    Channel* m_channel;
    RefreshModel* m_refreshModel;
    Song* m_currentSong;
};

#endif // SONGSMODEL_H
