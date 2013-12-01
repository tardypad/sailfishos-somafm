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
#include "src/Song/SongsModel.h"
#include "src/Song/SongsBookmarksManager.h"
#include "src/Song/SongsBookmarksProxyModel.h"
#include "src/News/NewsModel.h"
#include "src/Support/SupportModel.h"
#include "src/Player.h"
#include "src/Settings.h"

int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
    QScopedPointer<QQuickView> view(SailfishApp::createView());

    QQmlContext* context = view->rootContext();

    qmlRegisterUncreatableType<XmlItem>("my.library", 1, 0, "XmlItem", "");
    qmlRegisterUncreatableType<Channel>("my.library", 1, 0, "Channel", "");

    QScopedPointer<ChannelsModel> channelsModel(new ChannelsModel());
    QScopedPointer<ChannelsProxyModel> channelsProxyModel(new ChannelsProxyModel());
    channelsProxyModel->setSourceModel(channelsModel.data());
    context->setContextProperty("_channelsModel", channelsProxyModel.data());

    QScopedPointer<ChannelsFavoritesManager> favoritesManager(ChannelsFavoritesManager::instance());
    context->setContextProperty("_favoritesManager", favoritesManager.data());

    QScopedPointer<SongsModel> channelSongsModel(new SongsModel());
    context->setContextProperty("_channelSongsModel", channelSongsModel.data());

    QScopedPointer<SongsBookmarksManager> bookmarksManager(SongsBookmarksManager::instance());
    QScopedPointer<SongsBookmarksProxyModel> songsBookmarkProxyModel(new SongsBookmarksProxyModel());
    songsBookmarkProxyModel->setSourceModel(bookmarksManager.data());
    context->setContextProperty("_bookmarksManager", songsBookmarkProxyModel.data());

    QScopedPointer<NewsModel> newsModel(new NewsModel());
    context->setContextProperty("_newsModel", newsModel.data());

    QScopedPointer<SupportModel> supportModel(new SupportModel());
    context->setContextProperty("_supportModel", supportModel.data());

    QScopedPointer<Player> player(new Player());
    context->setContextProperty("_player", player.data());

    QScopedPointer<Settings> settings(new Settings());
    context->setContextProperty("_settings", settings.data());

    view->setSource(SailfishApp::pathTo("qml/SomaFM.qml"));
    view->show();

    return app->exec();
}
