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
    Q_INVOKABLE QUrl supportUrl();
    Q_INVOKABLE QUrl twitterUrl();
    Q_INVOKABLE QUrl facebookUrl();

protected:
    NewsModel* newsSourceModel();
};

#endif // NEWSPROXYMODEL_H
