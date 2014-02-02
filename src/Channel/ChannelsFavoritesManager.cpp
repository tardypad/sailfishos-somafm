/**
 *
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
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
