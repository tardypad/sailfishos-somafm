/**
 * Copyright (c) 2013-2019 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

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
    m_djMail(""),
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
    roleNames[DjMailRole] = "djMail";
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
    case DjMailRole:
        return djMail();
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
    case DjMailRole:
        setDjMail(value.toString());
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

XmlItem *Channel::create(QObject *parent)
{
    return new Channel(parent);
}

XmlItem *Channel::clone()
{
    Channel* newChannel = (Channel*) XmlItem::clone();

    StreamQuality quality;
    StreamFormat format;
    QUrl pls;

    for (int f = FirstFormat; f <= LastFormat; ++f) {
        format = (StreamFormat) f;
        QMapIterator<StreamQuality, QUrl> iterator(plsContainer(format));
        while (iterator.hasNext()) {
            iterator.next();
            quality = iterator.key();
            pls = iterator.value();
            newChannel->addPls(pls, format, quality);
        }
    }

    return newChannel;
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

QMap<Channel::StreamQuality, QMap<Channel::StreamFormat, QUrl> > Channel::getAllPlsQuality()
{
    QMap<StreamQuality, QMap<StreamFormat, QUrl> > result;
    QMap<StreamFormat, QUrl> qualityPls;
    StreamQuality quality;

    for (int q = FirstQuality; q <= LastQuality; ++q) {
        quality = (StreamQuality) q;
        qualityPls.clear();

        if (m_aacpPls.contains(quality))
            qualityPls.insert(AacPlusFormat, m_aacpPls.value(quality));
        if (m_aacPls.contains(quality))
            qualityPls.insert(AacFormat, m_aacPls.value(quality));
        if (m_mp3Pls.contains(quality))
            qualityPls.insert(Mp3Format, m_mp3Pls.value(quality));

        if (!qualityPls.empty())
            result.insert(quality, qualityPls);
    }

    return result;
}

QString Channel::streamQualityText(Channel::StreamQuality quality)
{
    switch (quality) {
    case TopQuality:
        return "Top";
    case GoodQuality:
        return "Good";
    case LowQuality:
        return "Low";
    }

    return defaultStreamQualityText();
}

Channel::StreamQuality Channel::streamQuality(QString quality)
{
    if (quality.compare("top", Qt::CaseInsensitive) == 0) {
        return TopQuality;
    } else if (quality.compare("good", Qt::CaseInsensitive) == 0) {
        return GoodQuality;
    } else if (quality.compare("low", Qt::CaseInsensitive) == 0) {
        return LowQuality;
    }

    return defaultStreamQuality();
}

QString Channel::streamFormatText(Channel::StreamFormat format)
{
    switch (format) {
    case AacPlusFormat:
        return "AAC+";
    case AacFormat:
        return "AAC";
    case Mp3Format:
        return "MP3";
    }

    return defaultStreamFormatText();
}

Channel::StreamFormat Channel::streamFormat(QString format)
{
    if (format.compare("aac+", Qt::CaseInsensitive) == 0) {
        return AacPlusFormat;
    } else if (format.compare("aac", Qt::CaseInsensitive) == 0) {
        return AacFormat;
    } else if (format.compare("mp3", Qt::CaseInsensitive) == 0) {
        return Mp3Format;
    }

    return defaultStreamFormat();
}

Channel::StreamQuality Channel::defaultStreamQuality()
{
    return GoodQuality;
}

Channel::StreamFormat Channel::defaultStreamFormat()
{
    return Mp3Format;
}

QString Channel::defaultStreamQualityText()
{
    return streamQualityText(defaultStreamQuality());
}

QString Channel::defaultStreamFormatText()
{
    return streamFormatText(defaultStreamFormat());
}

QList<QString> Channel::streamQualityTextList()
{
    QList<QString> qualities;
    for (int q = FirstQuality; q <= LastQuality; ++q) {
        qualities.append(streamQualityText( (Channel::StreamQuality) q ));
    }
    return qualities;
}

QList<QString> Channel::streamFormatTextList()
{
    QList<QString> formats;
    for (int f = FirstFormat; f <= LastFormat; ++f) {
        formats.append(streamFormatText( (Channel::StreamFormat) f ));
    }
    return formats;
}

QMap<Channel::StreamQuality, QUrl> Channel::plsContainer(Channel::StreamFormat format)
{
    switch (format) {
    case AacPlusFormat:
        return m_aacpPls;
    case AacFormat:
        return m_aacPls;
    case Mp3Format:
        return m_mp3Pls;
    }

    return QMap<StreamQuality, QUrl>();
}
