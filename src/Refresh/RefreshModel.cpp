#include "RefreshModel.h"

#include <QDebug>
#include <QStringList>
#include <QXmlStreamReader>
#include <QXmlStreamAttributes>

#include "../Channel/Channel.h"

#include "Refresh.h"

const QUrl RefreshModel::_refreshUrl = QUrl("http://somafm.com/refresh.xml");

RefreshModel::RefreshModel(QObject *parent) :
    XmlItemModel(new Refresh(), parent)
{
    setResourceUrl(_refreshUrl);
}

QMap<QString, QVariant> RefreshModel::playing(Channel* channel)
{
    QMap<QString, QVariant> result;

    QString channelId = channel->data(Channel::IdRole).toString();
    QVariant artist, song;

    for (int row = 0; row < m_list.size(); ++row) {
        if (m_list.at(row)->data(Refresh::ChannelIdRole).toString() == channelId) {
            artist = m_list.at(row)->data(Refresh::ArtistRole);
            song = m_list.at(row)->data(Refresh::SongRole);
            result.insert("artist", artist);
            result.insert("song", song);
            return result;
        }
    }

    return result;
}

XmlItem* RefreshModel::parseXmlItem()
{
    Refresh* refresh = new Refresh(this);
    QString channelId = "";
    QString listeners = "";
    QString artist = "";
    QString song = "";

    QXmlStreamAttributes attributes = m_xmlReader->attributes();
    channelId = attributes.value("id").toString();

    while (!m_xmlReader->atEnd() &&
           !(m_xmlReader->isEndElement() && m_xmlReader->name() == m_xmlItemPrototype->xmlTag())) {
        m_xmlReader->readNext();
        if (m_xmlReader->isStartElement()) {
            if (m_xmlReader->name() == "listeners") {
                m_xmlReader->readNext();
                listeners = m_xmlReader->text().toString();
            } else if (m_xmlReader->name() == "lastPlaying") {
                m_xmlReader->readNext();
                QString delimiter(" - ");
                QStringList lastPlaying = m_xmlReader->text().toString().split(delimiter);
                artist = lastPlaying.at(0);
                song = lastPlaying.at(1);
            }
        }
    }

    if (m_xmlReader->hasError())
        return NULL;

    refresh->setData(channelId, Refresh::ChannelIdRole);
    refresh->setData(listeners, Refresh::ListenersRole);
    refresh->setData(artist, Refresh::ArtistRole);
    refresh->setData(song, Refresh::SongRole);

    return refresh;
}
