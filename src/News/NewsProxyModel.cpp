/**
 * Copyright (c) 2013-2019 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

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
