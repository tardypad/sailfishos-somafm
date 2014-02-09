/**
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
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
