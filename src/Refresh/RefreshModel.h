#ifndef REFRESHMODEL_H
#define REFRESHMODEL_H

#include <QUrl>

#include "../XmlItem/XmlItemModel.h"

class Channel;

class RefreshModel : public XmlItemModel
{
    static const QUrl _refreshUrl;

    Q_OBJECT
public:
    explicit RefreshModel(QObject *parent = 0);
    Q_INVOKABLE QMap<QString, QVariant> playing(Channel* channel);

private:
    virtual XmlItem* parseXmlItem();
};

#endif // REFRESHMODEL_H
