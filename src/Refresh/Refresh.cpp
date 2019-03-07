/**
 * Copyright (c) 2013-2019 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

#include "Refresh.h"

#include <QDebug>

Refresh::Refresh(QObject *parent) :
    XmlItem(parent),
    m_channelId(""),
    m_listeners(0),
    m_artist(""),
    m_title("")
{
}

QHash<int, QByteArray> Refresh::roleNames()
{
    QHash<int, QByteArray> roleNames = XmlItem::roleNames();

    roleNames[ChannelIdRole] = "channelId";
    roleNames[ListenersRole] = "listeners";
    roleNames[ArtistRole] = "artist";
    roleNames[TitleRole] = "title";

    return roleNames;
}

QHash<int, QByteArray> Refresh::idRoleNames()
{
    QHash<int, QByteArray> idRoleNames;

    idRoleNames[ChannelIdRole] = "channelId";

    return idRoleNames;
}

QVariant Refresh::data(int role) const
{
    switch(role) {
    case ChannelIdRole:
        return channelId();
    case ListenersRole:
        return listeners();
    case ArtistRole:
        return artist();
    case TitleRole:
        return title();
    }

    return XmlItem::data(role);
}

bool Refresh::setData(const QVariant &value, int role)
{
    switch(role) {
    case ChannelIdRole:
        setChannelId(value.toString());
        return true;
    case ListenersRole:
        setListeners(value.toInt());
        return true;
    case ArtistRole:
        setArtist(value.toString());
        return true;
    case TitleRole:
        setTitle(value.toString());
        return true;
    }

    return XmlItem::setData(value, role);
}

XmlItem* Refresh::create(QObject *parent)
{
    return new Refresh(parent);
}
