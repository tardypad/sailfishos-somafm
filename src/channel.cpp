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
    m_genre(""),
    m_listeners(-1)
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
    roleNames[GenreRole] = "genre";
    roleNames[ListenersRole] = "listeners";

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
    case GenreRole:
        return genre();
    case ListenersRole:
        return listeners();
    default:
        return QVariant();
    }
}
