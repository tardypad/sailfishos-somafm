#include "channelsModel.h"

#include <QXmlStreamReader>
#include <QXmlStreamAttributes>

#include "channel.h"
#include "favoritesManager.h"

ChannelsModel::ChannelsModel(QObject *parent) :
    XmlModel(new Channel(), parent)
{
    setResourceUrl(QUrl("http://somafm.com/channels.xml"));

    m_favoritesManager = FavoritesManager::instance();
    connect(m_favoritesManager, SIGNAL(favoriteAdded(QString)), this, SLOT(addToFavorites(QString)));
    connect(m_favoritesManager, SIGNAL(favoriteRemoved(QString)), this, SLOT(removeFromFavorites(QString)));
}

ChannelsModel::~ChannelsModel()
{
}

void ChannelsModel::setDataChannel(QString channelId, const QVariant &value, int role)
{
    for (int row = 0; row < m_list.size(); ++row) {
        QString id = m_list.at(row)->data(Channel::IdRole).toString();
        if (id == channelId) {
            m_list.at(row)->setData(value, role);
        }
      }
}

XmlItem* ChannelsModel::parseXmlItem()
{
    Channel* channel = new Channel();

    QXmlStreamAttributes attributes = m_xmlReader->attributes();
    QString id = attributes.value("id").toString();
    channel->setData(id, Channel::IdRole);

    while (!(m_xmlReader->isEndElement() && m_xmlReader->name() == "channel")) {
        m_xmlReader->readNext();
        if (m_xmlReader->isStartElement()) {
            if (m_xmlReader->name() == "title") {
                m_xmlReader->readNext();
                QString name = m_xmlReader->text().toString();
                channel->setData(name, Channel::NameRole);
            } else if (m_xmlReader->name() == "description") {
                m_xmlReader->readNext();
                QString description = m_xmlReader->text().toString();
                channel->setData(description, Channel::DescriptionRole);
            } else if (m_xmlReader->name() == "image") {
                m_xmlReader->readNext();
                QString imageUrl = m_xmlReader->text().toString();
                channel->setData(imageUrl, Channel::ImageUrlRole);
            } else if (m_xmlReader->name() == "largeimage") {
                m_xmlReader->readNext();
                QString imageMediumUrl = m_xmlReader->text().toString();
                channel->setData(imageMediumUrl, Channel::ImageMediumUrlRole);
            } else if (m_xmlReader->name() == "xlimage") {
                m_xmlReader->readNext();
                QString imageBigUrl = m_xmlReader->text().toString();
                channel->setData(imageBigUrl, Channel::ImageBigUrlRole);
            } else if (m_xmlReader->name() == "dj") {
                m_xmlReader->readNext();
                QString dj = m_xmlReader->text().toString();
                channel->setData(dj, Channel::DjRole);
            } else if (m_xmlReader->name() == "genre") {
                m_xmlReader->readNext();
                QString genre = m_xmlReader->text().toString();
                QString delimiter("|");
                QStringList genres = genre.split(delimiter);
                channel->setData(genres, Channel::GenresRole);
                channel->setData(genres.at(0), Channel::SortGenreRole);
            } else if (m_xmlReader->name() == "listeners") {
                m_xmlReader->readNext();
                QString listeners = m_xmlReader->text().toString();
                channel->setData(listeners, Channel::ListenersRole);
            }
        }
    }

    if (m_favoritesManager->isFavorite(id)) {
        channel->setData(true, Channel::IsFavoriteRole);
    }

    duplicateGenre(channel);

    return channel;
}

void ChannelsModel::duplicateGenre(Channel *channel)
{
    QStringList genres = channel->data(Channel::GenresRole).toStringList();
    if (genres.size() > 1) {
        channel->setData(genres.at(0), Channel::SortGenreRole);
        for (int i = 1; i < genres.size(); ++i) {
            Channel* newChannel = channel->clone();
            newChannel->setData(genres.at(i), Channel::SortGenreRole);
            addXmlItem(newChannel);
        }
    }
}

void ChannelsModel::addToFavorites(QString channelId)
{
    setDataChannel(channelId, true, Channel::IsFavoriteRole);
}

void ChannelsModel::removeFromFavorites(QString channelId)
{
    setDataChannel(channelId, false, Channel::IsFavoriteRole);
}
