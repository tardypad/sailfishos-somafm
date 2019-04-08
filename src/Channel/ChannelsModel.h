/**
 * Copyright (c) 2013-2019 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

#ifndef CHANNELSMODEL_H
#define CHANNELSMODEL_H

#include "../XmlItem/XmlItemModel.h"

class Channel;
class RefreshModel;
class QNetworkAccessManager;

class ChannelsModel : public XmlItemModel
{
    static const QUrl _channelsUrl;

    Q_OBJECT
public:
    explicit ChannelsModel(QObject *parent = 0);
    ~ChannelsModel();
    Channel* channelItem(QString channelId);
    QMap<QString, QVariant> channelItemNameData(QString channelId);
    QMap<QString, QVariant> channelStreams(QString channelId);

private slots:
    void addToFavorites(XmlItem* xmlItem);
    void removeFromFavorites(XmlItem* xmlItem);
    void removeAllFromFavorites();
    void updateListeners();
    void onFetchImageFinished(QNetworkReply* networkReply);

private:
    virtual XmlItem* parseXmlItem();
    void parseChannelPls(Channel* channel);
    virtual void parseAfter();
    void duplicateGenre();
    void duplicateGenre(const QModelIndex &index);
    void calculMaximumListeners();
    void cacheImages();
    void fetchImage(QString id, QUrl imageUrl);
    QString imagesDirPath();
    void saveImage(QString id, QByteArray data);

private:
    RefreshModel* m_refreshModel;
    QNetworkAccessManager* m_imagesNetworkManager;
};

#endif // CHANNELSMODEL_H
