/**
 * Copyright (c) 2013-2019 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

#ifndef CHANNELSPROXYMODEL_H
#define CHANNELSPROXYMODEL_H

#include "../XmlItem/XmlItemProxyModel.h"

class XmlItem;
class Channel;
class ChannelsModel;

class ChannelsProxyModel : public XmlItemProxyModel
{
    Q_OBJECT
public:
    explicit ChannelsProxyModel(QObject *parent = 0);
    virtual bool lessThan(const QModelIndex &left, const QModelIndex &right) const;
    Q_INVOKABLE void sortByListeners();
    Q_INVOKABLE void sortByGenres();
    Q_INVOKABLE void sortByName();
    Q_INVOKABLE void filterFavorites();
    Q_INVOKABLE Channel* channelItem(QString channelId);
    Q_INVOKABLE QMap<QString, QVariant> channelItemNameData(QString channelId);
    Q_INVOKABLE QList<QString> streamsQualities();
    Q_INVOKABLE QList<QString> streamsFormats();
    Q_INVOKABLE QMap<QString, QVariant> channelStreams(QString channelId);

protected:
    ChannelsModel* channelsSourceModel();
};

#endif // CHANNELSPROXYMODEL_H
