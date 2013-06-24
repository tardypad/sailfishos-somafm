
#include <QApplication>
#include <QDeclarativeView>

#include "sailfishapplication.h"

#include <QDeclarativeContext>
#include <QSortFilterProxyModel>

#include "src/channelsModel.h"
#include "src/channelsProxyModel.h"
#include "src/channelsFavoritesManager.h"
#include "src/songsModel.h"
#include "src/songsBookmarksManager.h"
#include "src/newsModel.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(Sailfish::createApplication(argc, argv));
    QScopedPointer<QDeclarativeView> view(Sailfish::createView("main.qml"));
    
    ChannelsModel* channelsModel = new ChannelsModel();
    channelsModel->fetch();
    ChannelsProxyModel* channelsProxyModel = new ChannelsProxyModel();
    channelsProxyModel->setSourceModel(channelsModel);
    view->rootContext()->setContextProperty("_channelsModel", channelsProxyModel);

    ChannelsFavoritesManager* favoritesManager = ChannelsFavoritesManager::instance();
    view->rootContext()->setContextProperty("_favoritesManager", favoritesManager);

    SongsModel* channelSongsModel = new SongsModel();
    view->rootContext()->setContextProperty("_channelSongsModel", channelSongsModel);

    SongsBookmarksManager* bookmarksManager = SongsBookmarksManager::instance();
    view->rootContext()->setContextProperty("_bookmarksManager", bookmarksManager);

    NewsModel* newsModel = new NewsModel();
    newsModel->fetch();
    view->rootContext()->setContextProperty("_newsModel", newsModel);

    Sailfish::showView(view.data());
    
    return app->exec();
}


