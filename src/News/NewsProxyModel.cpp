#include "NewsProxyModel.h"

#include "News.h"
#include "NewsModel.h"

NewsProxyModel::NewsProxyModel(QObject *parent) :
    XmlItemProxyModel(parent)
{
}

NewsModel *NewsProxyModel::newsSourceModel()
{
    return (NewsModel*) sourceModel();
}

void NewsProxyModel::sortByDate()
{
    setSortRole(News::DateRole);
    sort(0, Qt::DescendingOrder);
}

QString NewsProxyModel::banner()
{
    return newsSourceModel()->banner();
}

QUrl NewsProxyModel::supportUrl()
{
    return newsSourceModel()->supportUrl();
}

QUrl NewsProxyModel::twitterUrl()
{
    return newsSourceModel()->twitterUrl();
}

QUrl NewsProxyModel::facebookUrl()
{
    return newsSourceModel()->facebookUrl();
}
