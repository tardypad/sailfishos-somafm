#ifndef SONGSPROXYMODEL_H
#define SONGSPROXYMODEL_H

#include "../XmlItem/XmlItemProxyModel.h"

class SongsModel;

class SongsProxyModel : public XmlItemProxyModel
{
    Q_OBJECT
public:
    explicit SongsProxyModel(QObject *parent = 0);
    Q_INVOKABLE void setChannel(XmlItem* channel);
    Q_INVOKABLE void fetchAdditional();
    Q_INVOKABLE void sortByDate();

signals:
    void fetchUpdateStarted();
    void fetchUpdateFinished();

protected slots:
    virtual void init();

protected:
    SongsModel* songsSourceModel();
};

#endif // SONGSPROXYMODEL_H
