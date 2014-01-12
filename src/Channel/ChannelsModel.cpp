#include "ChannelsModel.h"

#include <QDebug>
#include <QXmlStreamReader>
#include <QXmlStreamAttributes>

#include "Channel.h"
#include "ChannelsFavoritesManager.h"
#include "../Refresh/RefreshModel.h"

const QUrl ChannelsModel::_channelsUrl = QUrl("http://somafm.com/channels.xml");

ChannelsModel::ChannelsModel(QObject *parent) :
    XmlItemModel(new Channel(), parent)
{
    setResourceUrl(_channelsUrl);

    m_bookmarksManager = ChannelsFavoritesManager::instance();
    connect(m_bookmarksManager, SIGNAL(bookmarkAdded(XmlItem*)), this, SLOT(addToFavorites(XmlItem*)));
    connect(m_bookmarksManager, SIGNAL(bookmarkRemoved(XmlItem*)), this, SLOT(removeFromFavorites(XmlItem*)));
    connect(m_bookmarksManager, SIGNAL(allBookmarksRemoved()), this, SLOT(removeAllFromFavorites()));

    m_refreshModel = RefreshModel::instance();
    connect(m_refreshModel, SIGNAL(refreshed()), this, SLOT(updateListeners()));
}

ChannelsModel::~ChannelsModel()
{
}

XmlItem* ChannelsModel::parseXmlItem()
{
    Channel* channel = new Channel(this);
    QString id = "";
    QString name = "";
    QString description = "";
    QString imageUrl = "";
    QString imageMediumUrl = "";
    QString imageBigUrl = "";
    QString dj = "";
    QString djMail = "";
    QStringList genres = QStringList();
    QString sortGenre = "";
    QString listeners = "";

    QXmlStreamAttributes attributes = m_xmlReader->attributes();
    id = attributes.value("id").toString();

    while (!m_xmlReader->atEnd() &&
           !(m_xmlReader->isEndElement() && m_xmlReader->name() == m_xmlItemPrototype->xmlTag())) {
        m_xmlReader->readNext();
        if (m_xmlReader->isStartElement()) {
            if (m_xmlReader->name() == "title") {
                m_xmlReader->readNext();
                name = m_xmlReader->text().toString();
            } else if (m_xmlReader->name() == "description") {
                m_xmlReader->readNext();
                description = m_xmlReader->text().toString();
            } else if (m_xmlReader->name() == "image") {
                m_xmlReader->readNext();
                imageUrl = m_xmlReader->text().toString();
            } else if (m_xmlReader->name() == "largeimage") {
                m_xmlReader->readNext();
                imageMediumUrl = m_xmlReader->text().toString();
            } else if (m_xmlReader->name() == "xlimage") {
                m_xmlReader->readNext();
                imageBigUrl = m_xmlReader->text().toString();
            } else if (m_xmlReader->name() == "dj") {
                m_xmlReader->readNext();
                dj = m_xmlReader->text().toString();
            } else if (m_xmlReader->name() == "djmail") {
                m_xmlReader->readNext();
                djMail = m_xmlReader->text().toString();
            } else if (m_xmlReader->name() == "genre") {
                m_xmlReader->readNext();
                QString genre = m_xmlReader->text().toString();
                QString delimiter("|");
                genres = genre.split(delimiter);
                sortGenre = genres.at(0);
            } else if (m_xmlReader->name() == "listeners") {
                m_xmlReader->readNext();
                listeners = m_xmlReader->text().toString();
            } else if (m_xmlReader->name() == "highestpls"
            || m_xmlReader->name() == "fastpls"
            || m_xmlReader->name() == "slowpls") {
                parseChannelPls(channel);
            }
        }
    }

    if (m_xmlReader->hasError()) {
        delete channel;
        return NULL;
    }

    channel->setData(id, Channel::IdRole);
    channel->setData(name, Channel::NameRole);
    channel->setData(description, Channel::DescriptionRole);
    channel->setData(dj, Channel::DjRole);
    channel->setData(djMail, Channel::DjMailRole);
    channel->setData(genres, Channel::GenresRole);
    channel->setData(sortGenre, Channel::SortGenreRole);
    channel->setData(listeners, Channel::ListenersRole);

    channel->setData(imageUrl, Channel::ImageUrlRole);
    if (!imageMediumUrl.isEmpty()) {
        channel->setData(imageMediumUrl, Channel::ImageMediumUrlRole);
    } else if (!imageBigUrl.isEmpty()) {
        channel->setData(imageBigUrl, Channel::ImageMediumUrlRole);
    } else {
        channel->setData(imageUrl, Channel::ImageMediumUrlRole);
    }
    if (!imageBigUrl.isEmpty()) {
        channel->setData(imageBigUrl, Channel::ImageBigUrlRole);
    } else if (!imageMediumUrl.isEmpty()){
        channel->setData(imageMediumUrl, Channel::ImageBigUrlRole);
    } else {
        channel->setData(imageUrl, Channel::ImageBigUrlRole);
    }

    if (m_bookmarksManager->isBookmark(channel)) {
        channel->setData(true, Channel::IsBookmarkRole);
        channel->setData(m_bookmarksManager->getBookmarkDate(channel), Channel::BookmarkDateRole);
    }

    return channel;
}

void ChannelsModel::parseChannelPls(Channel *channel)
{
    QString qualityAtt = m_xmlReader->name().toString();
    Channel::StreamQuality quality;
    if (qualityAtt == "highestpls") {
        quality = Channel::TopQuality;
    } else if (qualityAtt == "fastpls") {
        quality = Channel::GoodQuality;
    } else if (qualityAtt == "slowpls") {
        quality = Channel::LowQuality;
    } else {
        return;
    }

    QString formatAtt = m_xmlReader->attributes().value("format").toString();
    Channel::StreamFormat format;
    if (formatAtt == "mp3") {
        format = Channel::Mp3Format;
    } else if (formatAtt == "aac") {
        format = Channel::AacFormat;
    } else if (formatAtt == "aacp") {
        format = Channel::AacPlusFormat;
    }  else {
        return;
    }

    m_xmlReader->readNext();
    QUrl pls = m_xmlReader->text().toString();

    channel->addPls(pls, format, quality);
}

void ChannelsModel::parseAfter()
{
    duplicateGenre();
    calculMaximumListeners();
}

Channel *ChannelsModel::channelItem(QString channelId)
{
    for (int row = 0; row < m_list.size(); ++row) {
      if (m_list.at(row)->data(Channel::IdRole).toString() == channelId)
          return (Channel*) m_list.at(row);
    }
    return NULL;
}

QMap<QString, QVariant> ChannelsModel::channelItemNameData(QString channelId)
{
    QMap<QString, QVariant> result;

    Channel* channel = channelItem(channelId);
    if (!channel) return result;

    QHash<int, QByteArray> roleNames = m_xmlItemPrototype->roleNames();

    QHashIterator<int, QByteArray> iterator(roleNames);
    QVariant itemValue;
    QString roleName;
    int roleInt;

    while (iterator.hasNext()) {
        iterator.next();
        roleInt = iterator.key();
        roleName = QString(iterator.value());
        itemValue = channel->data(roleInt);
        result.insert(roleName, itemValue);
    }

    return result;
}

QMap<QString, QVariant> ChannelsModel::channelStreams(QString channelId)
{
    QMap<QString, QVariant> result;

    Channel* channel = channelItem(channelId);
    QMap<Channel::StreamQuality, QMap<Channel::StreamFormat, QUrl> > allPls = channel->getAllPlsQuality();

    QMapIterator<Channel::StreamQuality, QMap<Channel::StreamFormat, QUrl> > iterator(allPls);
    QString quality, format;
    while (iterator.hasNext()) {
        iterator.next();
        quality = Channel::streamQualityText(iterator.key());
        QMapIterator<Channel::StreamFormat, QUrl> iterator2(iterator.value());
        while (iterator2.hasNext()) {
            iterator2.next();
            format = Channel::streamFormatText(iterator2.key());
            result.insertMulti(quality, format);
        }
    }

    return result;
}

void ChannelsModel::duplicateGenre()
{
    for (int row = 0; row < m_list.size(); ++row) {
        duplicateGenre(index(row));
    }
}

void ChannelsModel::duplicateGenre(const QModelIndex &index)
{
    Channel* channel = (Channel*) m_list.at(index.row());

    QStringList genres = channel->data(Channel::GenresRole).toStringList();
    bool isClone = channel->data(Channel::IsCloneRole).toBool();

    if (!isClone && genres.size() > 1) {
        setData(index, genres.at(0), Channel::SortGenreRole);
        for (int i = 1; i < genres.size(); ++i) {
            Channel* newChannel = (Channel*) channel->clone();
            newChannel->setData(genres.at(i), Channel::SortGenreRole);
            appendXmlItem(newChannel);
        }
    }
}

void ChannelsModel::addToFavorites(XmlItem *xmlItem)
{
   addToBookmarks(xmlItem);
}


void ChannelsModel::removeFromFavorites(XmlItem *xmlItem)
{
    removeFromBookmarks(xmlItem);
}

void ChannelsModel::removeAllFromFavorites()
{
    removeAllFromBookmarks();
}

void ChannelsModel::updateListeners()
{
    int listeners;
    Channel* channel;

    for(int row = 0; row < m_list.size(); ++row) {
        channel = (Channel*) m_list.at(row);
        listeners = m_refreshModel->listeners(channel);
        channel->setData(listeners, Channel::ListenersRole);
    }

    calculMaximumListeners();
}

void ChannelsModel::calculMaximumListeners()
{
    int max = 0, channelListeners;

    for(int row = 0; row < m_list.size(); ++row) {
        channelListeners = m_list.at(row)->data(Channel::ListenersRole).toInt() ;
        if (channelListeners > max)
            max = channelListeners;
    }

    setDataAll(max, Channel::MaximumListenersRole);
}
