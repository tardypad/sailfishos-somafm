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


#include "Refresh.h"

#include <QDebug>

Refresh::Refresh(QObject *parent) :
    XmlItem(parent),
    m_channelId(""),
    m_listeners(0),
    m_artist(""),
    m_title("")
{
}

QHash<int, QByteArray> Refresh::roleNames()
{
    QHash<int, QByteArray> roleNames = XmlItem::roleNames();

    roleNames[ChannelIdRole] = "channelId";
    roleNames[ListenersRole] = "listeners";
    roleNames[ArtistRole] = "artist";
    roleNames[TitleRole] = "title";

    return roleNames;
}

QHash<int, QByteArray> Refresh::idRoleNames()
{
    QHash<int, QByteArray> idRoleNames;

    idRoleNames[ChannelIdRole] = "channelId";

    return idRoleNames;
}

QVariant Refresh::data(int role) const
{
    switch(role) {
    case ChannelIdRole:
        return channelId();
    case ListenersRole:
        return listeners();
    case ArtistRole:
        return artist();
    case TitleRole:
        return title();
    }

    return XmlItem::data(role);
}

bool Refresh::setData(const QVariant &value, int role)
{
    switch(role) {
    case ChannelIdRole:
        setChannelId(value.toString());
        return true;
    case ListenersRole:
        setListeners(value.toInt());
        return true;
    case ArtistRole:
        setArtist(value.toString());
        return true;
    case TitleRole:
        setTitle(value.toString());
        return true;
    }

    return XmlItem::setData(value, role);
}

XmlItem* Refresh::create(QObject *parent)
{
    return new Refresh(parent);
}
