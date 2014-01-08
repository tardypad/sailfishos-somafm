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
        SongRole
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
    inline QString song() const { return m_song; }

    inline void setChannelId(QString channelId) { m_channelId = channelId; }
    inline void setListeners(int listeners) { m_listeners = listeners; }
    inline void setArtist(QString artist) { m_artist = artist; }
    inline void setSong(QString song) { m_song = song; }

private:
    QString m_channelId;
    int m_listeners;
    QString m_artist;
    QString m_song;
};

#endif // REFRESH_H
