
#include <QApplication>
#include <QDeclarativeView>

#include "sailfishapplication.h"

#include <QDeclarativeContext>

#include "src/channelsmodel.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(Sailfish::createApplication(argc, argv));
    QScopedPointer<QDeclarativeView> view(Sailfish::createView("main.qml"));
    
    ChannelsModel* channelsModel = new ChannelsModel();
    channelsModel->fetch();
    view->rootContext()->setContextProperty("channelsModel", channelsModel);

    Sailfish::showView(view.data());
    
    return app->exec();
}


