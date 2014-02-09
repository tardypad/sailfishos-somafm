/**
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

#ifndef NEWSPROXYMODEL_H
#define NEWSPROXYMODEL_H

#include <QUrl>

#include "../XmlItem/XmlItemProxyModel.h"

class NewsModel;

class NewsProxyModel : public XmlItemProxyModel
{
    Q_OBJECT
public:
    explicit NewsProxyModel(QObject *parent = 0);
    Q_INVOKABLE void sortByDate();
    Q_INVOKABLE QString banner();

protected:
    NewsModel* newsSourceModel();
};

#endif // NEWSPROXYMODEL_H
