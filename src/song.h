#ifndef SONG_H
#define SONG_H

#include <QObject>
#include <QHash>
#include <QByteArray>
#include <QVariant>
#include <QString>
#include <QDateTime>

#include "xmlItem.h"

class Song : public XmlItem
{
    Q_OBJECT

public:
    enum Roles {
        TitleRole = Qt::UserRole+1,
        ArtistRole,
        AlbumRole,
        DateRole,
        IsBookmarkRole
    };

public:
    explicit Song(QObject *parent = 0);
    virtual QVariant data(int role) const;
    virtual bool setData (const QVariant &value, int role);
    virtual QHash<int, QByteArray> roleNames();

    virtual QString xmlTag() { return "song"; }

    inline QString title() const { return m_title; }
    inline QString artist() const { return m_artist; }
    inline QString album() const { return m_album; }
    inline QDateTime date() const { return m_date; }
    inline bool isBookmark() const { return m_isBookmark; }

    inline void setTitle(QString title) { m_title = title; }
    inline void setArtist(QString artist) { m_artist = artist; }
    inline void setAlbum(QString album) { m_album = album; }
    inline void setDate(QDateTime date) { m_date = date; }
    inline void setIsBookmark(bool isBookmark) { m_isBookmark = isBookmark; }

private:
    QString m_title;
    QString m_artist;
    QString m_album;
    QDateTime m_date;
    bool m_isBookmark;
};

#endif // SONG_H