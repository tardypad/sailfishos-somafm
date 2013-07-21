#include "channel.h"

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
    m_sortGenre("")
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

    return roleNames;
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
    }

    return XmlItem::setData(value, role);
}

Channel* Channel::clone()
{
    Channel* newChannel = new Channel();
    newChannel->setId(id());
    newChannel->setName(name());
    newChannel->setDescription(description());
    newChannel->setImageUrl(imageUrl());
    newChannel->setImageMediumUrl(imageMediumUrl());
    newChannel->setImageBigUrl(imageBigUrl());
    newChannel->setDj(dj());
    newChannel->setGenres(genres());
    newChannel->setListeners(listeners());
    newChannel->setSortGenre(sortGenre());
    newChannel->setIsClone(true);
    newChannel->setIsBookmark(isBookmark());

    return newChannel;
}
