/**
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

#include "ChannelsFavoritesManager.h"

#include <QDebug>

#include "Channel.h"
#include "ChannelsFavoritesDatabaseManager.h"

ChannelsFavoritesManager* ChannelsFavoritesManager::m_instance = NULL;

ChannelsFavoritesManager::ChannelsFavoritesManager(QObject *parent) :
    XmlItemBookmarkManager(new Channel(), parent)
{
    m_databaseManager = ChannelsFavoritesDatabaseManager::instance();
    load();
}

ChannelsFavoritesManager* ChannelsFavoritesManager::instance()
{
    if (!m_instance) {
        m_instance = new ChannelsFavoritesManager();
    }

    return m_instance;
}

bool ChannelsFavoritesManager::addFavorite(XmlItem *xmlItem)
{
    return addBookmark(xmlItem);
}

bool ChannelsFavoritesManager::removeFavorite(XmlItem *xmlItem)
{
    return removeBookmark(xmlItem);
}
