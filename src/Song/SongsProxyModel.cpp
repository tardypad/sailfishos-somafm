/**
 * Copyright (c) 2013-2019 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

#include "SongsProxyModel.h"

#include "SongsModel.h"
#include "Song.h"

SongsProxyModel::SongsProxyModel(QObject *parent) :
    XmlItemProxyModel(parent)
{
}

SongsModel *SongsProxyModel::songsSourceModel()
{
    return (SongsModel*) sourceModel();
}

void SongsProxyModel::init()
{
    XmlItemProxyModel::init();
    connect(songsSourceModel(), SIGNAL(fetchUpdateStarted()), this, SIGNAL(fetchUpdateStarted()));
    connect(songsSourceModel(), SIGNAL(fetchUpdateFinished()), this, SIGNAL(fetchUpdateFinished()));
}

void SongsProxyModel::setChannel(XmlItem *channel)
{
    return songsSourceModel()->setChannel(channel);
}

void SongsProxyModel::fetchAdditional()
{
    return songsSourceModel()->fetchAdditional();
}

void SongsProxyModel::sortByDate()
{
    setSortRole(Song::DateRole);
    sort(0, Qt::DescendingOrder);
}
