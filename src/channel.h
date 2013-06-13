#ifndef CHANNEL_H
#define CHANNEL_H

#include <QObject>
#include <QHash>
#include <QByteArray>
#include <QVariant>
#include <QString>
#include <QUrl>
#include <QStringList>

class Channel : public QObject
{
    Q_OBJECT

public:
    enum Roles {
        IdRole = Qt::UserRole+1,
        NameRole,
        DescriptionRole,
        ImageUrlRole,
        ImageMediumUrlRole,
        ImageBigUrlRole,
        DjRole,
        GenresRole,
        ListenersRole,
        SortGenreRole,
        IsCloneRole
    };

public:
    explicit Channel(QObject *parent = 0);
    QVariant data(int role) const;
    static QHash<int, QByteArray> roleNames();
    Channel* clone();

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
    inline bool isClone() const { return m_isClone; }

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
    inline void setIsClone(bool isClone) { m_isClone = isClone; }
    
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
    bool m_isClone;
    
};

#endif // CHANNEL_H
