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


#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>

#include <QDebug>
#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>
#include <QtQml>

#include "src/XmlItem/XmlItem.h"
#include "src/Channel/Channel.h"
#include "src/Channel/ChannelsModel.h"
#include "src/Channel/ChannelsProxyModel.h"
#include "src/Channel/ChannelsFavoritesManager.h"
#include "src/Song/Song.h"
#include "src/Song/SongsModel.h"
#include "src/Song/SongsProxyModel.h"
#include "src/Song/SongsBookmarksManager.h"
#include "src/Song/SongsBookmarksProxyModel.h"
#include "src/News/NewsModel.h"
#include "src/News/NewsProxyModel.h"
#include "src/Support/SupportModel.h"
#include "src/Refresh/RefreshModel.h"
#include "src/Player.h"
#include "src/Settings.h"

int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
    QScopedPointer<QQuickView> view(SailfishApp::createView());

    QQmlContext* context = view->rootContext();

    qmlRegisterUncreatableType<XmlItem>("my.library", 1, 0, "XmlItem", "");
    qmlRegisterUncreatableType<Channel>("my.library", 1, 0, "Channel", "");
    qmlRegisterUncreatableType<Song>("my.library", 1, 0, "Song", "");

    QCoreApplication::setOrganizationName("SomaFM.com");
    QCoreApplication::setOrganizationDomain("somafm.com");
    QCoreApplication::setApplicationName("SomaFM");
    QCoreApplication::setApplicationVersion("0.2");

    QScopedPointer<ChannelsModel> channelsModel(new ChannelsModel());
    QScopedPointer<ChannelsProxyModel> channelsProxyModel(new ChannelsProxyModel());
    channelsProxyModel->setSourceModel(channelsModel.data());
    context->setContextProperty("_channelsModel", channelsProxyModel.data());

    QScopedPointer<ChannelsFavoritesManager> favoritesManager(ChannelsFavoritesManager::instance());
    context->setContextProperty("_favoritesManager", favoritesManager.data());

    QScopedPointer<SongsModel> channelSongsModel(new SongsModel());
    QScopedPointer<SongsProxyModel> channelSongsProxyModel(new SongsProxyModel());
    channelSongsProxyModel->setSourceModel(channelSongsModel.data());
    context->setContextProperty("_channelSongsModel", channelSongsProxyModel.data());

    QScopedPointer<SongsBookmarksManager> bookmarksManager(SongsBookmarksManager::instance());
    QScopedPointer<SongsBookmarksProxyModel> songsBookmarkProxyModel(new SongsBookmarksProxyModel());
    songsBookmarkProxyModel->setSourceModel(bookmarksManager.data());
    context->setContextProperty("_bookmarksManager", songsBookmarkProxyModel.data());

    QScopedPointer<NewsModel> newsModel(new NewsModel());
    QScopedPointer<NewsProxyModel> newsProxyModel(new NewsProxyModel());
    newsProxyModel->setSourceModel(newsModel.data());
    context->setContextProperty("_newsModel", newsProxyModel.data());

    QScopedPointer<SupportModel> supportModel(new SupportModel());
    context->setContextProperty("_supportModel", supportModel.data());

    QScopedPointer<RefreshModel> refreshModel(RefreshModel::instance());
    context->setContextProperty("_refreshModel", refreshModel.data());

    QScopedPointer<Player> player(new Player());
    context->setContextProperty("_player", player.data());

    QScopedPointer<Settings> settings(new Settings());
    context->setContextProperty("_settings", settings.data());

    view->setSource(SailfishApp::pathTo("qml/harbour-somafm.qml"));
    view->show();

    return app->exec();
}
