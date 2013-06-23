
#include <QApplication>
#include <QDeclarativeView>

#include "sailfishapplication.h"

#include <QDeclarativeContext>
#include <QSortFilterProxyModel>

#include "src/channelsModel.h"
#include "src/channelsProxyModel.h"
#include "src/favoritesManager.h"
#include "src/channelSongsModel.h"
#include "src/bookmarksManager.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(Sailfish::createApplication(argc, argv));
    QScopedPointer<QDeclarativeView> view(Sailfish::createView("main.qml"));
    
    ChannelsModel* channelsModel = new ChannelsModel();
    channelsModel->fetch();
    ChannelsProxyModel* channelsProxyModel = new ChannelsProxyModel();
    channelsProxyModel->setSourceModel(channelsModel);
    view->rootContext()->setContextProperty("_channelsModel", channelsProxyModel);

    FavoritesManager* favoritesManager = FavoritesManager::instance();
    view->rootContext()->setContextProperty("_favoritesManager", favoritesManager);

    ChannelSongsModel* channelSongsModel = new ChannelSongsModel();
    view->rootContext()->setContextProperty("_channelSongsModel", channelSongsModel);

    BookmarksManager* bookmarksManager = BookmarksManager::instance();
    view->rootContext()->setContextProperty("_bookmarksManager", bookmarksManager);

    Sailfish::showView(view.data());
    
    return app->exec();
}


