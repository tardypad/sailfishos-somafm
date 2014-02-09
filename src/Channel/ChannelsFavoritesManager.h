/**
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

#ifndef CHANNELSFAVORITESMANAGER_H
#define CHANNELSFAVORITESMANAGER_H

#include "../XmlItem/XmlItemBookmarkManager.h"

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
