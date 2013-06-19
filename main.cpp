
#include <QApplication>
#include <QDeclarativeView>

#include "sailfishapplication.h"

#include <QDeclarativeContext>
#include <QSortFilterProxyModel>

#include "src/channelsModel.h"
#include "src/channelsProxyModel.h"
#include "src/favoritesManager.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(Sailfish::createApplication(argc, argv));
    QScopedPointer<QDeclarativeView> view(Sailfish::createView("main.qml"));
    
    ChannelsModel* channelsModel = new ChannelsModel();
    channelsModel->fetch();
    ChannelsProxyModel* channelsProxyModel = new ChannelsProxyModel();
    channelsProxyModel->setSourceModel(channelsModel);
    view->rootContext()->setContextProperty("_channelsModel", channelsProxyModel);

    FavoritesManager* favoritesManager = new FavoritesManager();
    view->rootContext()->setContextProperty("_favoritesManager", favoritesManager);

    channelsModel->setFavoritesManager(favoritesManager);

    Sailfish::showView(view.data());
    
    return app->exec();
}


