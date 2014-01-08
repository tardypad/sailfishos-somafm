#include "Refresh.h"

#include <QDebug>

Refresh::Refresh(QObject *parent) :
    XmlItem(parent),
    m_channelId(""),
    m_listeners(0),
    m_artist(""),
    m_song("")
{
}

QHash<int, QByteArray> Refresh::roleNames()
{
    QHash<int, QByteArray> roleNames = XmlItem::roleNames();

    roleNames[ChannelIdRole] = "channelId";
    roleNames[ListenersRole] = "listeners";
    roleNames[ArtistRole] = "artist";
    roleNames[SongRole] = "song";

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
    case SongRole:
        return song();
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
    case SongRole:
        setSong(value.toString());
        return true;
    }

    return XmlItem::setData(value, role);
}

XmlItem* Refresh::create(QObject *parent)
{
    return new Refresh(parent);
}
