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


#ifndef REFRESH_H
#define REFRESH_H

#include "../XmlItem/XmlItem.h"

class Refresh : public XmlItem
{
    Q_OBJECT

public:
    enum Roles {
        ChannelIdRole = XmlItem::LastRole + 1,
        ListenersRole,
        ArtistRole,
        TitleRole
    };

public:
    explicit Refresh(QObject *parent = 0);
    virtual QVariant data(int role) const;
    virtual bool setData (const QVariant &value, int role);
    virtual QHash<int, QByteArray> roleNames();
    virtual QHash<int, QByteArray> idRoleNames();
    virtual XmlItem* create(QObject *parent);

    virtual QString xmlTag() { return "channel"; }

    inline QString channelId() const { return m_channelId; }
    inline int listeners() const { return m_listeners; }
    inline QString artist() const { return m_artist; }
    inline QString title() const { return m_title; }

    inline void setChannelId(QString channelId) { m_channelId = channelId; }
    inline void setListeners(int listeners) { m_listeners = listeners; }
    inline void setArtist(QString artist) { m_artist = artist; }
    inline void setTitle(QString title) { m_title = title; }

private:
    QString m_channelId;
    int m_listeners;
    QString m_artist;
    QString m_title;
};

#endif // REFRESH_H
