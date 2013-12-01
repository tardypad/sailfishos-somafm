#ifndef CHANNEL_H
#define CHANNEL_H

#include <QObject>
#include <QHash>
#include <QByteArray>
#include <QVariant>
#include <QString>
#include <QUrl>
#include <QStringList>

#include "../XmlItem/XmlItem.h"

class Channel : public XmlItem
{
    Q_OBJECT

public:    
    enum Roles {
        IdRole = XmlItem::LastRole + 1,
        NameRole,
        DescriptionRole,
        ImageUrlRole,
        ImageMediumUrlRole,
        ImageBigUrlRole,
        DjRole,
        GenresRole,
        ListenersRole,
        SortGenreRole,
        MaximumListenersRole
    };

    enum StreamQuality {
        TopQuality,
        GoodQuality,
        LowQuality,
        FirstQuality = TopQuality,
        LastQuality = LowQuality
    };

    enum StreamFormat {
        AacPlusFormat,
        AacFormat,
        Mp3Format,
        FirstFormat = AacPlusFormat,
        LastFormat = Mp3Format
    };

public:
    explicit Channel(QObject *parent = 0);
    virtual QVariant data(int role) const;
    virtual bool setData (const QVariant &value, int role);
    virtual QHash<int, QByteArray> roleNames();
    virtual QHash<int, QByteArray> bookmarkRoleNames();
    virtual QHash<int, QByteArray> idRoleNames();
    virtual XmlItem* create();
    void addPls(QUrl pls, StreamFormat format, StreamQuality quality);

    static QString streamQuality(StreamQuality quality);
    static QString streamFormat(StreamFormat format);
    static QString defaultStreamQuality();
    static QString defaultStreamFormat();

    virtual QString xmlTag() { return "channel"; }

    inline QString id() const { return m_id; }
    inline QString name() const { return m_name; }
    inline QString description() const { return m_description; }
    inline QUrl imageUrl() const { return m_imageUrl; }
    inline QUrl imageMediumUrl() const { return m_imageMediumUrl; }
    inline QUrl imageBigUrl() const { return m_imageBigUrl; }
    inline QString dj() const { return m_dj; }
    inline QStringList genres() const { return m_genres; }
    inline int listeners() const { return m_listeners; }
    inline QString sortGenre() const { return m_sortGenre; }
    inline int maximumListeners() const { return m_maximumListeners; }

    inline void setId(QString id) { m_id = id; }
    inline void setName(QString name) { m_name = name; }
    inline void setDescription(QString description) { m_description = description; }
    inline void setImageUrl(QUrl imageUrl) { m_imageUrl = imageUrl; }
    inline void setImageMediumUrl(QUrl imageMediumUrl) { m_imageMediumUrl = imageMediumUrl; }
    inline void setImageBigUrl(QUrl imageBigUrl) { m_imageBigUrl = imageBigUrl; }
    inline void setDj(QString dj) { m_dj = dj; }
    inline void setGenres(QStringList genres) { m_genres = genres; }
    inline void setListeners(int listeners) { m_listeners = listeners; }
    inline void setSortGenre(QString sortGenre) { m_sortGenre = sortGenre; }
    inline void setMaximumListeners(int maximumListeners) { m_maximumListeners = maximumListeners; }

private:
    QString m_id;
    QString m_name;
    QString m_description;
    QUrl m_imageUrl;
    QUrl m_imageMediumUrl;
    QUrl m_imageBigUrl;
    QString m_dj;
    QStringList m_genres;
    int m_listeners;
    QString m_sortGenre;
    int m_maximumListeners;
    QMap<StreamQuality, QUrl> m_mp3Pls;
    QMap<StreamQuality, QUrl> m_aacPls;
    QMap<StreamQuality, QUrl> m_aacpPls;
};

#endif // CHANNEL_H
