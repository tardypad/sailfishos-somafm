#ifndef SONG_H
#define SONG_H

#include <QObject>
#include <QHash>
#include <QByteArray>
#include <QVariant>
#include <QString>
#include <QDateTime>
#include <QUrl>

#include "../XmlItem/XmlItem.h"

class Song : public XmlItem
{
    Q_OBJECT

public:
    enum Roles {
        TitleRole = XmlItem::LastRole + 1,
        ArtistRole,
        AlbumRole,
        DateRole,
        ChannelIdRole,
        ChannelNameRole,
        ChannelImageUrlRole
    };

public:
    explicit Song(QObject *parent = 0);
    virtual QVariant data(int role) const;
    virtual bool setData (const QVariant &value, int role);
    virtual QHash<int, QByteArray> roleNames();
    virtual QHash<int, QByteArray> bookmarkRoleNames();
    virtual QHash<int, QByteArray> idRoleNames();
    virtual XmlItem* create();

    virtual QString xmlTag() { return "song"; }

    inline QString title() const { return m_title; }
    inline QString artist() const { return m_artist; }
    inline QString album() const { return m_album; }
    inline QDateTime date() const { return m_date; }
    inline QString channelId() const { return m_channelId; }
    inline QString channelName() const { return m_channelName; }
    inline QUrl channelImageUrl() const { return m_channelImageUrl; }

    inline void setTitle(QString title) { m_title = title; }
    inline void setArtist(QString artist) { m_artist = artist; }
    inline void setAlbum(QString album) { m_album = album; }
    inline void setDate(QDateTime date) { m_date = date; }
    inline void setChannelId(QString channelId) { m_channelId = channelId; }
    inline void setChannelName(QString channelName) { m_channelName = channelName; }
    inline void setChannelImageUrl(QUrl channelImageUrl) { m_channelImageUrl = channelImageUrl; }

private:
    QString m_title;
    QString m_artist;
    QString m_album;
    QDateTime m_date;
    QString m_channelId;
    QString m_channelName;
    QUrl m_channelImageUrl;
};

#endif // SONG_H
