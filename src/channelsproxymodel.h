#ifndef CHANNELSPROXYMODEL_H
#define CHANNELSPROXYMODEL_H

#include <QSortFilterProxyModel>

class ChannelsProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit ChannelsProxyModel(QObject *parent = 0);
    Q_INVOKABLE void sortByListeners();
};

#endif // CHANNELSPROXYMODEL_H
