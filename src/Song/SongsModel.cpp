#include "SongsModel.h"

#include <QDebug>
#include <QXmlStreamReader>
#include <QtNetwork/QNetworkReply>

#include "Song.h"
#include "../Channel/Channel.h"
#include "SongsBookmarksManager.h"
#include "../Refresh/RefreshModel.h"

const QUrl SongsModel::_channelSongsUrl = QUrl("http://somafm.com/songs/:channelId:.xml");

SongsModel::SongsModel(QObject *parent) :
    XmlItemModel(new Song(), parent),
    m_channel(NULL),
    m_currentSong(new Song(this))
{
    m_bookmarksManager = SongsBookmarksManager::instance();    
    connect(m_bookmarksManager, SIGNAL(bookmarkAdded(XmlItem*)), this, SLOT(addToBookmarks(XmlItem*)));
    connect(m_bookmarksManager, SIGNAL(bookmarkRemoved(XmlItem*)), this, SLOT(removeFromBookmarks(XmlItem*)));
    connect(m_bookmarksManager, SIGNAL(allBookmarksRemoved()), this, SLOT(removeAllFromBookmarks()));
    connect(m_bookmarksManager, SIGNAL(allChannelBookmarksRemoved(QString)), this, SLOT(removeAllFromChannelBookmarks(QString)));

    m_refreshModel = RefreshModel::instance();
    connect(m_refreshModel, SIGNAL(refreshed()), this, SLOT(updateCurrentSong()));
}

SongsModel::~SongsModel()
{
    delete m_currentSong;
}

void SongsModel::setChannel(XmlItem *channel)
{
    m_channel = (Channel*) channel;
    QString channelId = m_channel->data(Channel::IdRole).toString();
    QString url = _channelSongsUrl.url();
    url.replace(":channelId:", channelId);
    setResourceUrl(url);
    updateCurrentSong();
}

void SongsModel::fetchAdditional()
{
    launchDownload();
    emit fetchUpdateStarted();
    connect(m_currentReply, SIGNAL(finished()), this, SLOT(parseAdditional()));
    connect(m_currentReply, SIGNAL(finished()), this, SIGNAL(fetchUpdateFinished()));
}

void SongsModel::parseAdditional()
{
    if (m_currentReply->error() != QNetworkReply::NoError)
        return;

    m_xmlReader->clear();

    QByteArray data = m_currentReply->readAll();
    m_xmlReader->addData(data);

    while (!m_xmlReader->atEnd()) {
        m_xmlReader->readNext();
        if (m_xmlReader->isStartElement()) {
            if (m_xmlReader->name() == m_xmlItemPrototype->xmlTag()) {
                XmlItem* xmlItem = parseXmlItem();

                if (!xmlItem)
                    return;

                if (!includeXmlItem(xmlItem)) {
                    delete xmlItem;
                    continue;
                }

                if (!contains(xmlItem))
                    preprendXmlItem(xmlItem);
            }
        }
    }
}

void SongsModel::removeAllFromChannelBookmarks(QString channelId)
{
    setDataItems(channelId, Song::ChannelIdRole, false, Song::IsBookmarkRole);
}

void SongsModel::updateCurrentSong()
{
    QMap<QString, QVariant> current = m_refreshModel->playing(m_channel);

    if (current.isEmpty()) return;

    QVariant artist = current.value("artist");
    QVariant song = current.value("song");

    m_currentSong->setData(artist, Song::ArtistRole);
    m_currentSong->setData(song, Song::TitleRole);

    setDataItem(m_currentSong, true, Song::IsCurrentRole, false, false);
}

bool SongsModel::includeXmlItem(XmlItem *xmlItem)
{
    QDateTime date = xmlItem->data(Song::DateRole).toDateTime();

    return date > QDateTime::currentDateTime().addSecs(-3600);
}

XmlItem* SongsModel::parseXmlItem()
{
    QString title = "";
    QString artist = "";
    QString album = "";
    QDateTime datetime = QDateTime();
    QString channelId = m_channel->data(Channel::IdRole).toString();
    QString channelName = m_channel->data(Channel::NameRole).toString();
    QUrl channelImageUrl = m_channel->data(Channel::ImageUrlRole).toString();

    while (!m_xmlReader->atEnd() &&
           !(m_xmlReader->isEndElement() && m_xmlReader->name() == m_xmlItemPrototype->xmlTag())) {
        m_xmlReader->readNext();
        if (m_xmlReader->isStartElement()) {
            if (m_xmlReader->name() == "title") {
                m_xmlReader->readNext();
                title = m_xmlReader->text().toString();
            } else if (m_xmlReader->name() == "artist") {
                m_xmlReader->readNext();
                artist = m_xmlReader->text().toString();
            } else if (m_xmlReader->name() == "album") {
                m_xmlReader->readNext();
                album = m_xmlReader->text().toString();
            } else if (m_xmlReader->name() == "date") {
                m_xmlReader->readNext();
                int timestamp = m_xmlReader->text().toString().toInt();
                datetime = QDateTime::fromTime_t(timestamp);
            }
        }
    }

    if (m_xmlReader->hasError())
        return NULL;

    Song* song = new Song(this);

    song->setData(title, Song::TitleRole);
    song->setData(artist, Song::ArtistRole);
    song->setData(album, Song::AlbumRole);
    song->setData(datetime, Song::DateRole);
    song->setData(channelId, Song::ChannelIdRole);
    song->setData(channelName, Song::ChannelNameRole);
    song->setData(channelImageUrl, Song::ChannelImageUrlRole);

    if (m_bookmarksManager->isBookmark(song)) {
        song->setData(true, Song::IsBookmarkRole);
    }

    if (m_currentSong->isEqual(song)) {
        song->setData(true, Song::IsCurrentRole);
    }

    return song;
}
