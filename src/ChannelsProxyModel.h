#ifndef CHANNELSPROXYMODEL_H
#define CHANNELSPROXYMODEL_H

#include "XmlItemProxyModel.h"

class XmlItem;

class ChannelsProxyModel : public XmlItemProxyModel
{
    Q_OBJECT
public:
    explicit ChannelsProxyModel(QObject *parent = 0);
    Q_INVOKABLE void sortByListeners();
    Q_INVOKABLE void sortByGenres();
    Q_INVOKABLE void sortByName();
    Q_INVOKABLE void filterFavorites();
};

#endif // CHANNELSPROXYMODEL_H
