#include "song.h"

Song::Song(QObject *parent) :
    XmlItem(parent),
    m_title(""),
    m_artist(""),
    m_album(""),
    m_date(QDateTime()),
    m_isBookmark(false)
{
}

QHash<int, QByteArray> Song::roleNames()
{
    QHash<int, QByteArray> roleNames;
    roleNames[TitleRole] = "title";
    roleNames[ArtistRole] = "artist";
    roleNames[AlbumRole] = "album";
    roleNames[DateRole] = "date";
    roleNames[IsBookmarkRole] = "isBookmark";

    return roleNames;
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
    case IsBookmarkRole:
        return isBookmark();
    }

    return QVariant();
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
    case IsBookmarkRole:
        setIsBookmark(value.toBool());
        return true;
    }

    return false;
}
