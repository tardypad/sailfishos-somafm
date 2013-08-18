#include <QGuiApplication>
#include <QQuickView>

#include "sailfishapplication.h"

#include <QDebug>
#include <QQmlContext>
#include <QSortFilterProxyModel>
#include <QtQml>

#include "src/XmlItem.h"
#include "src/ChannelsModel.h"
#include "src/ChannelsProxyModel.h"
#include "src/ChannelsFavoritesManager.h"
#include "src/SongsModel.h"
#include "src/SongsBookmarksManager.h"
#include "src/NewsModel.h"

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
