#ifndef CHANNELSFAVORITESMANAGER_H
#define CHANNELSFAVORITESMANAGER_H

#include <QObject>
#include <QStringList>

class ChannelsFavoritesManager : public QObject
{
    Q_OBJECT
public:
    static ChannelsFavoritesManager* instance();
    Q_INVOKABLE bool addFavorite(QString channelId);
    Q_INVOKABLE bool removeFavorite(QString channelId);
    QStringList getFavorites() const;
    bool isFavorite(QString channelId) const;

signals:
    void favoriteAdded(QString id);
    void favoriteRemoved(QString id);

private:
    explicit ChannelsFavoritesManager(QObject *parent = 0);

private:
    static ChannelsFavoritesManager* m_instance;
    QStringList m_favorites;
};

#endif // CHANNELSFAVORITESMANAGER_H
