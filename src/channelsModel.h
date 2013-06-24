#ifndef CHANNELSMODEL_H
#define CHANNELSMODEL_H

#include "xmlModel.h"

class Channel;
class ChannelsFavoritesManager;

class ChannelsModel : public XmlModel
{
    Q_OBJECT
public:
    explicit ChannelsModel(QObject *parent = 0);
    ~ChannelsModel();
    void setDataChannel(QString channelId, const QVariant &value, int role);

private slots:
    void addToFavorites(QString channelId);
    void removeFromFavorites(QString channelId);

private:
    virtual XmlItem* parseXmlItem();
    void duplicateGenre(Channel* channel);

private:
    ChannelsFavoritesManager* m_favoritesManager;
};

#endif // CHANNELSMODEL_H
