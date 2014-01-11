#include "Song.h"

#include <QDebug>

Song::Song(QObject *parent) :
    XmlItem(parent),
    m_title(""),
    m_artist(""),
    m_album(""),
    m_date(QDateTime()),
    m_channelId(""),
    m_channelName(""),
    m_channelImageUrl(""),
    m_isCurrent(false)
{
}

QHash<int, QByteArray> Song::roleNames()
{
    QHash<int, QByteArray> roleNames = XmlItem::roleNames();

    roleNames[TitleRole] = "title";
    roleNames[ArtistRole] = "artist";
    roleNames[AlbumRole] = "album";
    roleNames[DateRole] = "date";
    roleNames[ChannelIdRole] = "channelId";
    roleNames[ChannelNameRole] = "channelName";
    roleNames[ChannelImageUrlRole] = "channelImageUrl";
    roleNames[IsCurrentRole] = "isCurrent";

    return roleNames;
}

QHash<int, QByteArray> Song::bookmarkRoleNames()
{
    QHash<int, QByteArray> bookmarkRoleNames = XmlItem::bookmarkRoleNames();

    bookmarkRoleNames[TitleRole] = "title";
    bookmarkRoleNames[ArtistRole] = "artist";
    bookmarkRoleNames[AlbumRole] = "album";
    bookmarkRoleNames[ChannelIdRole] = "channelId";
    bookmarkRoleNames[ChannelNameRole] = "channelName";
    bookmarkRoleNames[ChannelImageUrlRole] = "channelImageUrl";

    return bookmarkRoleNames;
}

QHash<int, QByteArray> Song::idRoleNames()
{
    QHash<int, QByteArray> idRoleNames;

    idRoleNames[TitleRole] = "title";
    idRoleNames[ArtistRole] = "artist";

    return idRoleNames;
}

QVariant Song::data(int role) const
{
    switch(role) {
    case TitleRole:
        return title();
    case ArtistRole:
        return artist();
    case AlbumRole:
        return album();
    case DateRole:
        return date();
    case ChannelIdRole:
        return channelId();
    case ChannelNameRole:
        return channelName();
    case ChannelImageUrlRole:
        return channelImageUrl();
    case IsCurrentRole:
        return isCurrent();
    }

    return XmlItem::data(role);
}

bool Song::setData(const QVariant &value, int role)
{
    switch(role) {
    case TitleRole:
        setTitle(value.toString());
        return true;
    case ArtistRole:
        setArtist(value.toString());
        return true;
    case AlbumRole:
        setAlbum(value.toString());
        return true;
    case DateRole:
        setDate(value.toDateTime());
        return true;
    case ChannelIdRole:
        setChannelId(value.toString());
        return true;
    case ChannelNameRole:
        setChannelName(value.toString());
        return true;
    case ChannelImageUrlRole:
        setChannelImageUrl(value.toUrl());
        return true;
    case IsCurrentRole:
        setIsCurrent(value.toBool());
        return true;
    }

    return XmlItem::setData(value, role);
}

XmlItem* Song::create(QObject *parent)
{
    return new Song(parent);
}

