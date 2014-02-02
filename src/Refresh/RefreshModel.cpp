/**
 *
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 **/


#include "RefreshModel.h"

#include <QDebug>
#include <QStringList>
#include <QXmlStreamReader>
#include <QXmlStreamAttributes>

#include "../Channel/Channel.h"

#include "Refresh.h"

const QUrl RefreshModel::_refreshUrl = QUrl("http://somafm.com/refresh.xml");

RefreshModel* RefreshModel::m_instance = NULL;

RefreshModel::RefreshModel(QObject *parent) :
    XmlItemModel(new Refresh(), parent)
{
    setClearBeforeFetching(false);
    setResourceUrl(_refreshUrl);
    connect(this, SIGNAL(dataParsed()), this, SIGNAL(refreshed()));
}

RefreshModel* RefreshModel::instance()
{
    if (!m_instance) {
        m_instance = new RefreshModel();
    }

    return m_instance;
}

QMap<QString, QVariant> RefreshModel::playing(Channel* channel)
{
    QMap<QString, QVariant> result;

    if (!channel) return result;

    QString channelId = channel->data(Channel::IdRole).toString();
    QVariant artist, title;

    for (int row = 0; row < m_list.size(); ++row) {
        if (m_list.at(row)->data(Refresh::ChannelIdRole).toString() == channelId) {
            artist = m_list.at(row)->data(Refresh::ArtistRole);
            title = m_list.at(row)->data(Refresh::TitleRole);
            result.insert("artist", artist);
            result.insert("title", title);
            return result;
        }
    }

    return result;
}

int RefreshModel::listeners(Channel *channel)
{
    if (!channel) return 0;

    QString channelId = channel->data(Channel::IdRole).toString();

    for (int row = 0; row < m_list.size(); ++row) {
        if (m_list.at(row)->data(Refresh::ChannelIdRole).toString() == channelId)
            return m_list.at(row)->data(Refresh::ListenersRole).toInt();
    }

    return 0;
}

XmlItem* RefreshModel::parseXmlItem()
{
    QString channelId = "";
    QString listeners = "";
    QString artist = "";
    QString title = "";

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
                title = lastPlaying.at(1);
            }
        }
    }

    if (m_xmlReader->hasError())
        return NULL;

    Refresh* refresh = getUpdateItem(channelId);

    refresh->setData(channelId, Refresh::ChannelIdRole);
    refresh->setData(listeners, Refresh::ListenersRole);
    refresh->setData(artist, Refresh::ArtistRole);
    refresh->setData(title, Refresh::TitleRole);

    return refresh;
}

Refresh *RefreshModel::getUpdateItem(QString channelId)
{
    for(int row = 0; row < m_list.size(); ++row) {
      if (m_list.at(row)->data(Refresh::ChannelIdRole) == channelId) {
          return (Refresh*) m_list.at(row);
      }
    }
    return (Refresh*) m_xmlItemPrototype->create(this);
}
