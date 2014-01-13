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
    virtual bool lessThan(const QModelIndex &left, const QModelIndex &right) const;
    Q_INVOKABLE void filterByChannel(QString channelId);
    Q_INVOKABLE void sortByChannel();
    Q_INVOKABLE QList<QVariant> channelIds();
    Q_INVOKABLE QMap<QString, QVariant> channelData(QString channelId);
    Q_INVOKABLE bool removeAllChannelBookmarks(QString channelId);

signals:
    void firstChannelBookmark(QString channelId);

protected slots:
    virtual void init();

protected:
    SongsBookmarksManager* songBookmarksManagerSourceModel();
};

#endif // SONGSBOOKMARKSPROXYMODEL_H
