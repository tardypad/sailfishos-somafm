#ifndef FAVORITESMANAGER_H
#define FAVORITES_H

#include <QObject>
#include <QStringList>

class FavoritesManager : public QObject
{
    Q_OBJECT
public:
    explicit FavoritesManager(QObject *parent = 0);
    Q_INVOKABLE bool addFavorite(QString channelId);
    Q_INVOKABLE bool removeFavorite(QString channelId);
    QStringList getFavorites() const;
    bool isFavorite(QString channelId) const;

signals:
    void favoriteAdded(QString id);
    void favoriteRemoved(QString id);

private:
    QStringList m_favorites;
};

#endif // FAVORITESMANAGER_H
