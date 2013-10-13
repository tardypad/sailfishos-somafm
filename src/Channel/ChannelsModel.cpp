#include "ChannelsModel.h"

#include <QDebug>
#include <QXmlStreamReader>
#include <QXmlStreamAttributes>

#include "Channel.h"
#include "ChannelsFavoritesManager.h"

const QUrl ChannelsModel::_channelsUrl = QUrl("http://somafm.com/channels.xml");

ChannelsModel::ChannelsModel(QObject *parent) :
    XmlItemModel(new Channel(), parent)
{
    setResourceUrl(_channelsUrl);

    m_bookmarksManager = ChannelsFavoritesManager::instance();
    connect(m_bookmarksManager, SIGNAL(bookmarkAdded(XmlItem*)), this, SLOT(addToFavorites(XmlItem*)));
    connect(m_bookmarksManager, SIGNAL(bookmarkRemoved(XmlItem*)), this, SLOT(removeFromFavorites(XmlItem*)));
}

ChannelsModel::~ChannelsModel()
{
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

    if (m_xmlReader->hasError())
        return NULL;

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

    if (m_bookmarksManager->isBookmark(channel)) {
        channel->setData(true, Channel::IsBookmarkRole);
        channel->setData(m_bookmarksManager->getBookmarkDate(channel), Channel::BookmarkDateRole);
    }

    return channel;
}

void ChannelsModel::parseAfter()
{
    duplicateGenre();
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
