#include "channelSongsModel.h"

#include <QXmlStreamReader>

#include "channelSong.h"

ChannelSongsModel::ChannelSongsModel(QObject *parent) :
    XmlModel(new ChannelSong(), parent)
{
}

ChannelSongsModel::~ChannelSongsModel()
{
}

void ChannelSongsModel::setChannelId(QString channelId)
{
    setResourceUrl(QUrl("http://somafm.com/songs/" + channelId + ".xml"));
}

XmlItem* ChannelSongsModel::parseXmlItem()
{
    ChannelSong* channelSong = new ChannelSong();

    while (!(m_xmlReader->isEndElement() && m_xmlReader->name() == "song")) {
        m_xmlReader->readNext();
        if (m_xmlReader->isStartElement()) {
            if (m_xmlReader->name() == "title") {
                m_xmlReader->readNext();
                QString title = m_xmlReader->text().toString();
                channelSong->setData(title, ChannelSong::TitleRole);
            } else if (m_xmlReader->name() == "artist") {
                m_xmlReader->readNext();
                QString artist = m_xmlReader->text().toString();
                channelSong->setData(artist, ChannelSong::ArtistRole);
            } else if (m_xmlReader->name() == "album") {
                m_xmlReader->readNext();
                QString album = m_xmlReader->text().toString();
                channelSong->setData(album, ChannelSong::AlbumRole);
            } else if (m_xmlReader->name() == "date") {
                m_xmlReader->readNext();
                int timestamp = m_xmlReader->text().toString().toInt();
                QDateTime date = QDateTime::fromTime_t(timestamp);
                channelSong->setData(date, ChannelSong::DateRole);
            }
        }
    }

    return channelSong;
}
