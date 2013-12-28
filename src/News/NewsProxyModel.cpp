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
