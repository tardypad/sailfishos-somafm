#include <QGuiApplication>
#include <QQuickView>

#include "sailfishapplication.h"

#include <QDebug>
#include <QQmlContext>
#include <QSortFilterProxyModel>
#include <QtQml>

#include "src/XmlItem/XmlItem.h"
#include "src/Channel/ChannelsModel.h"
#include "src/Channel/ChannelsProxyModel.h"
#include "src/Channel/ChannelsFavoritesManager.h"
#include "src/Song/SongsModel.h"
#include "src/Song/SongsBookmarksManager.h"
#include "src/Song/SongsBookmarksProxyModel.h"
#include "src/News/NewsModel.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> app(Sailfish::createApplication(argc, argv));
    QScopedPointer<QQuickView> view(Sailfish::createView("main.qml"));

    QQmlContext* context = view->rootContext();

    qmlRegisterUncreatableType<XmlItem>("my.library", 1, 0, "XmlItem", "");

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

    Sailfish::showView(view.data());

    return app->exec();
}
