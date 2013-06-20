#include "channelSong.h"

ChannelSong::ChannelSong(QObject *parent) :
    QObject(parent),
    m_title(""),
    m_artist(""),
    m_album(""),
    m_date(QDateTime())
{
}

QHash<int, QByteArray> ChannelSong::roleNames()
{
    QHash<int, QByteArray> roleNames;
    roleNames[TitleRole] = "title";
    roleNames[ArtistRole] = "artist";
    roleNames[AlbumRole] = "album";
    roleNames[DateRole] = "date";

    return roleNames;
}

QVariant ChannelSong::data(int role) const
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
    default:
        return QVariant();
    }
}

bool ChannelSong::setData(const QVariant &value, int role)
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
    }

    return false;
}
