#include "channelsModel.h"

#include <QXmlStreamReader>
#include <QXmlStreamAttributes>

#include "channel.h"
#include "channelsFavoritesManager.h"

ChannelsModel::ChannelsModel(QObject *parent) :
    XmlModel(new Channel(), parent)
{
    setResourceUrl(QUrl("http://somafm.com/channels.xml"));

    m_favoritesManager = ChannelsFavoritesManager::instance();
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
            setData(index(row), value, role);
        }
      }
}

XmlItem* ChannelsModel::parseXmlItem()
{
    Channel* channel = new Channel();
    QString id = "";
    QString name = "";
    QString description = "";
    QString imageUrl = "";
    QString imageMediumUrl = "";
    QString imageBigUrl = "";
    QString dj = "";
    QStringList genres = QStringList();
    QString sortGenre = "";
    QString listeners = "";

    QXmlStreamAttributes attributes = m_xmlReader->attributes();
    id = attributes.value("id").toString();


    while (!(m_xmlReader->isEndElement() && m_xmlReader->name() == m_xmlItemPrototype->xmlTag())) {
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
            } else if (m_xmlReader->name() == "genre") {
                m_xmlReader->readNext();
                QString genre = m_xmlReader->text().toString();
                QString delimiter("|");
                genres = genre.split(delimiter);
                sortGenre = genres.at(0);
            } else if (m_xmlReader->name() == "listeners") {
                m_xmlReader->readNext();
                listeners = m_xmlReader->text().toString();
            }
        }
    }

    channel->setData(id, Channel::IdRole);
    channel->setData(name, Channel::NameRole);
    channel->setData(description, Channel::DescriptionRole);
    channel->setData(imageUrl, Channel::ImageUrlRole);
    channel->setData(imageMediumUrl, Channel::ImageMediumUrlRole);
    channel->setData(imageBigUrl, Channel::ImageBigUrlRole);
    channel->setData(dj, Channel::DjRole);
    channel->setData(genres, Channel::GenresRole);
    channel->setData(sortGenre, Channel::SortGenreRole);
    channel->setData(listeners, Channel::ListenersRole);

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
