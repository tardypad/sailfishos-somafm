#include "favoritesManager.h"

FavoritesManager::FavoritesManager(QObject *parent) :
    QObject(parent), m_favorites("")
{
    // temporary initial favorites
    m_favorites.append("poptron");
    m_favorites.append("beatblender");
    m_favorites.append("spacestation");
}

bool FavoritesManager::addFavorite(QString channelId)
{
    if (isFavorite(channelId)) return false;

    m_favorites.append(channelId);
    emit favoriteAdded(channelId);

    return true;
}

bool FavoritesManager::removeFavorite(QString channelId)
{
    if (!isFavorite(channelId)) return false;

    m_favorites.removeOne(channelId);
    emit favoriteRemoved(channelId);

    return true;
}

QStringList FavoritesManager::getFavorites() const
{
    return m_favorites;
}

bool FavoritesManager::isFavorite(QString channelId) const
{
    return m_favorites.contains(channelId, Qt::CaseInsensitive);
}