#ifndef REFRESHMODEL_H
#define REFRESHMODEL_H

#include <QUrl>

#include "../XmlItem/XmlItemModel.h"

class Channel;
class Refresh;

class RefreshModel : public XmlItemModel
{
    static const QUrl _refreshUrl;

    Q_OBJECT
public:
    static RefreshModel* instance();
    Q_INVOKABLE QMap<QString, QVariant> playing(Channel* channel);

signals:
    void refreshed();

private:
    explicit RefreshModel(QObject *parent = 0);
    virtual XmlItem* parseXmlItem();
    Refresh* getUpdateItem(QString channelId);

private:
    static RefreshModel* m_instance;
};

#endif // REFRESHMODEL_H
