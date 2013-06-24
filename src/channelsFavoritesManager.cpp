#include "channelsFavoritesManager.h"

ChannelsFavoritesManager* ChannelsFavoritesManager::m_instance = NULL;

ChannelsFavoritesManager::ChannelsFavoritesManager(QObject *parent) :
    QObject(parent), m_favorites("")
{
    // temporary initial favorites
    m_favorites.append("poptron");
    m_favorites.append("beatblender");
    m_favorites.append("spacestation");
}

ChannelsFavoritesManager* ChannelsFavoritesManager::instance()
{
    if (!m_instance) {
        m_instance = new ChannelsFavoritesManager();
    }

    return m_instance;
}

bool ChannelsFavoritesManager::addFavorite(QString channelId)
{
    if (isFavorite(channelId)) return false;

    m_favorites.append(channelId);
    emit favoriteAdded(channelId);

    return true;
}

bool ChannelsFavoritesManager::removeFavorite(QString channelId)
{
    if (!isFavorite(channelId)) return false;

    m_favorites.removeOne(channelId);
    emit favoriteRemoved(channelId);

    return true;
}

QStringList ChannelsFavoritesManager::getFavorites() const
{
    return m_favorites;
}

bool ChannelsFavoritesManager::isFavorite(QString channelId) const
{
    return m_favorites.contains(channelId, Qt::CaseInsensitive);
}
