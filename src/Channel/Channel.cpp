#include "Channel.h"

#include <QDebug>

Channel::Channel(QObject *parent) :
    XmlItem(parent),
    m_id(""),
    m_name(""),
    m_description(""),
    m_imageUrl(""),
    m_imageMediumUrl(""),
    m_imageBigUrl(""),
    m_dj(""),
    m_genres(""),
    m_listeners(-1),
    m_sortGenre(""),
    m_maximumListeners(0),
    m_mp3Pls(QMap<StreamQuality, QUrl>()),
    m_aacPls(QMap<StreamQuality, QUrl>()),
    m_aacpPls(QMap<StreamQuality, QUrl>())
{
}

QHash<int, QByteArray> Channel::roleNames()
{
    QHash<int, QByteArray> roleNames = XmlItem::roleNames();

    roleNames[IdRole] = "id";
    roleNames[NameRole] = "name";
    roleNames[DescriptionRole] = "description";
    roleNames[ImageUrlRole] = "imageUrl";
    roleNames[ImageMediumUrlRole] = "imageMediumUrl";
    roleNames[ImageBigUrlRole] = "imageBigUrl";
    roleNames[DjRole] = "dj";
    roleNames[GenresRole] = "genres";
    roleNames[ListenersRole] = "listeners";
    roleNames[SortGenreRole] = "sortGenre";
    roleNames[MaximumListenersRole] = "maximumListeners";

    return roleNames;
}

QHash<int, QByteArray> Channel::bookmarkRoleNames()
{
    QHash<int, QByteArray> bookmarkRoleNames = XmlItem::bookmarkRoleNames();

    bookmarkRoleNames[IdRole] = "id";
    bookmarkRoleNames[NameRole] = "name";

    return bookmarkRoleNames;
}

QHash<int, QByteArray> Channel::idRoleNames()
{
    QHash<int, QByteArray> idRoleNames;

    idRoleNames[IdRole] = "id";

    return idRoleNames;
}

QVariant Channel::data(int role) const
{
    switch(role) {
    case IdRole:
        return id();
    case NameRole:
        return name();
    case DescriptionRole:
        return description();
    case ImageUrlRole:
        return imageUrl();
    case ImageMediumUrlRole:
        return imageMediumUrl();
    case ImageBigUrlRole:
        return imageBigUrl();
    case DjRole:
        return dj();
    case GenresRole:
        return genres();
    case ListenersRole:
        return listeners();
    case SortGenreRole:
        return sortGenre();
    case MaximumListenersRole:
        return maximumListeners();
    }

    return XmlItem::data(role);
}

bool Channel::setData(const QVariant &value, int role)
{
    switch(role) {
    case IdRole:
        setId(value.toString());
        return true;
    case NameRole:
        setName(value.toString());
        return true;
    case DescriptionRole:
        setDescription(value.toString());
        return true;
    case ImageUrlRole:
        setImageUrl(value.toUrl());
        return true;
    case ImageMediumUrlRole:
        setImageMediumUrl(value.toUrl());
        return true;
    case ImageBigUrlRole:
        setImageBigUrl(value.toUrl());
        return true;
    case DjRole:
        setDj(value.toString());
        return true;
    case GenresRole:
        setGenres(value.toStringList());
        return true;
    case ListenersRole:
        setListeners(value.toInt());
        return true;
    case SortGenreRole:
        setSortGenre(value.toString());
        return true;
    case MaximumListenersRole:
        setMaximumListeners(value.toInt());
        return true;
    }

    return XmlItem::setData(value, role);
}

XmlItem *Channel::create()
{
    return new Channel();
}

void Channel::addPls(QUrl pls, StreamFormat format, StreamQuality quality)
{
    switch (format) {
    case Mp3Format:
        m_mp3Pls.insertMulti(quality, pls);
        break;
    case AacFormat:
        m_aacPls.insertMulti(quality, pls);
        break;
    case AacPlusFormat:
        m_aacpPls.insertMulti(quality, pls);
        break;

    }
}

QString Channel::streamQuality(Channel::StreamQuality quality)
{
    switch (quality) {
    case TopQuality:
        return "Top";
    case GoodQuality:
        return "Good";
    case LowQuality:
        return "Low";
    }

    return "";
}

QString Channel::streamFormat(Channel::StreamFormat format)
{
    switch (format) {
    case AacPlusFormat:
        return "AAC+";
    case AacFormat:
        return "AAC";
    case Mp3Format:
        return "MP3";
    }

    return "";
}
