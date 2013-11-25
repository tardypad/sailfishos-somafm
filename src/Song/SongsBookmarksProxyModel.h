#ifndef SONGSBOOKMARKSPROXYMODEL_H
#define SONGSBOOKMARKSPROXYMODEL_H

#include "../XmlItem/XmlItemProxyBookmarkManager.h"

class XmlItem;
class SongsBookmarksManager;

class SongsBookmarksProxyModel : public XmlItemProxyBookmarkManager
{
    Q_OBJECT
public:
    explicit SongsBookmarksProxyModel(QObject *parent = 0);
    Q_INVOKABLE void filterByChannel(QString channelId);
    Q_INVOKABLE void sortByChannel();
    Q_INVOKABLE QList<QVariant> channelIds();
    Q_INVOKABLE QMap<QString, QVariant> channelData(QString channelId);

protected:
    SongsBookmarksManager* songBookmarksManagerSourceModel();
};

#endif // SONGSBOOKMARKSPROXYMODEL_H
