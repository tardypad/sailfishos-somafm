/**
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
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

    qmlRegisterUncreatableType<XmlItem>("SomaFM", 1, 0, "XmlItem", "");
    qmlRegisterUncreatableType<Channel>("SomaFM", 1, 0, "Channel", "");
    qmlRegisterUncreatableType<Song>("SomaFM", 1, 0, "Song", "");

    QCoreApplication::setOrganizationName("tardypad");
    QCoreApplication::setOrganizationDomain("tardypad.me");
    QCoreApplication::setApplicationName("SomaFM");
    QCoreApplication::setApplicationVersion("1.0.0");

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
