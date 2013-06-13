#include "channel.h"

Channel::Channel(QObject *parent) :
    QObject(parent),
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
    m_isClone(false)
{
}

QHash<int, QByteArray> Channel::roleNames()
{
    QHash<int, QByteArray> roleNames;
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
    roleNames[IsCloneRole] = "isClone";

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
    case IsCloneRole:
        return isClone();
    default:
        return QVariant();
    }
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

    return newChannel;
}
