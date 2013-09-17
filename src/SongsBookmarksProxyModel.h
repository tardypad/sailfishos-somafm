#ifndef SONGSBOOKMARKSPROXYMODEL_H
#define SONGSBOOKMARKSPROXYMODEL_H

#include "XmlItemProxyBookmarkManager.h"

class XmlItem;

class SongsBookmarksProxyModel : public XmlItemProxyBookmarkManager
{
    Q_OBJECT
public:
    explicit SongsBookmarksProxyModel(QObject *parent = 0);
    Q_INVOKABLE void sortByChannel();
};

#endif // SONGSBOOKMARKSPROXYMODEL_H
