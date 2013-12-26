#include "SongsProxyModel.h"

#include "SongsModel.h"
#include "Song.h"

SongsProxyModel::SongsProxyModel(QObject *parent) :
    XmlItemProxyModel(parent)
{
}

SongsModel *SongsProxyModel::songsSourceModel()
{
    return (SongsModel*) sourceModel();
}

void SongsProxyModel::setChannel(XmlItem *channel)
{
    return songsSourceModel()->setChannel(channel);
}

void SongsProxyModel::fetchAdditional()
{
    return songsSourceModel()->fetchAdditional();
}

void SongsProxyModel::sortByDate()
{
    setSortRole(Song::DateRole);
    sort(0, Qt::DescendingOrder);
}
