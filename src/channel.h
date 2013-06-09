#ifndef CHANNEL_H
#define CHANNEL_H

#include <QObject>
#include <QHash>
#include <QByteArray>
#include <QVariant>
#include <QString>
#include <QUrl>

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
        GenreRole,
        ListenersRole
    };

public:
    explicit Channel(QObject *parent = 0);
    QVariant data(int role) const;
    static QHash<int, QByteArray> roleNames();

    inline QString id() const { return m_id; }
    inline QString name() const { return m_name; }
    inline QString description() const { return m_description; }
    inline QUrl imageUrl() const { return m_imageUrl; }
    inline QUrl imageMediumUrl() const { return m_imageMediumUrl; }
    inline QUrl imageBigUrl() const { return m_imageBigUrl; }
    inline QString dj() const { return m_dj; }
    inline QString genre() const { return m_genre; }
    inline int listeners() const { return m_listeners; }

    inline void setId(QString id) { m_id = id; }
    inline void setName(QString name) { m_name = name; }
    inline void setDescription(QString description) { m_description = description; }
    inline void setImageUrl(QUrl imageUrl) { m_imageUrl = imageUrl; }
    inline void setImageMediumUrl(QUrl imageMediumUrl) { m_imageMediumUrl = imageMediumUrl; }
    inline void setImageBigUrl(QUrl imageBigUrl) { m_imageBigUrl = imageBigUrl; }
    inline void setDj(QString dj) { m_dj = dj; }
    inline void setGenre(QString genre) { m_genre = genre; }
    inline void setListeners(int listeners) { m_listeners = listeners; }
    
private:
    QString m_id;
    QString m_name;
    QString m_description;
    QUrl m_imageUrl;
    QUrl m_imageMediumUrl;
    QUrl m_imageBigUrl;
    QString m_dj;
    QString m_genre;
    int m_listeners;
    
};

#endif // CHANNEL_H
