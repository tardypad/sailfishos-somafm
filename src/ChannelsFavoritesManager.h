#ifndef CHANNELSFAVORITESMANAGER_H
#define CHANNELSFAVORITESMANAGER_H

#include "XmlItemBookmarkManager.h"

class ChannelsFavoritesManager : public XmlItemBookmarkManager
{
    Q_OBJECT
public:
    static ChannelsFavoritesManager* instance();
    Q_INVOKABLE bool addFavorite(XmlItem *xmlItem);
    Q_INVOKABLE bool removeFavorite(XmlItem *xmlItem);

private:
    explicit ChannelsFavoritesManager(QObject *parent = 0);

private:
    static ChannelsFavoritesManager* m_instance;
};

#endif // CHANNELSFAVORITESMANAGER_H
