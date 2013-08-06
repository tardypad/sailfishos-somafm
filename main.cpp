
#include <QGuiApplication>
#include <QQuickView>

#include "sailfishapplication.h"

#include <QQmlContext>
#include <QSortFilterProxyModel>
#include <QtQml>

#include "src/xmlItem.h"
#include "src/channelsModel.h"
#include "src/channelsProxyModel.h"
#include "src/channelsFavoritesManager.h"
#include "src/songsModel.h"
#include "src/songsBookmarksManager.h"
#include "src/newsModel.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> app(Sailfish::createApplication(argc, argv));
    QScopedPointer<QQuickView> view(Sailfish::createView("main.qml"));

    QQmlContext* context = view->rootContext();

    qmlRegisterUncreatableType<XmlItem>("my.library", 1, 0, "XmlItem", "");

    ChannelsModel* channelsModel = new ChannelsModel();
    channelsModel->fetch();
    ChannelsProxyModel* channelsProxyModel = new ChannelsProxyModel();
    channelsProxyModel->setSourceModel(channelsModel);
    context->setContextProperty("_channelsModel", channelsProxyModel);

    ChannelsFavoritesManager* favoritesManager = ChannelsFavoritesManager::instance();
    context->setContextProperty("_favoritesManager", favoritesManager);

    SongsModel* channelSongsModel = new SongsModel();
    context->setContextProperty("_channelSongsModel", channelSongsModel);

    SongsBookmarksManager* bookmarksManager = SongsBookmarksManager::instance();
    context->setContextProperty("_bookmarksManager", bookmarksManager);

    NewsModel* newsModel = new NewsModel();
    newsModel->fetch();
    context->setContextProperty("_newsModel", newsModel);

    Sailfish::showView(view.data());
    
    return app->exec();
}


