#ifndef CHANNELSMODEL_H
#define CHANNELSMODEL_H

#include "../XmlItem/XmlItemModel.h"

class Channel;

class ChannelsModel : public XmlItemModel
{
    static const QUrl _channelsUrl;

    Q_OBJECT
public:
    explicit ChannelsModel(QObject *parent = 0);
    ~ChannelsModel();
    Channel* channelItem(QString channelId);
    QMap<QString, QVariant> channelItemNameData(QString channelId);
    QMap<QString, QVariant> channelStreams(QString channelId);

private slots:
    void addToFavorites(XmlItem* xmlItem);
    void removeFromFavorites(XmlItem* xmlItem);
    void removeAllFromFavorites();

private:
    virtual XmlItem* parseXmlItem();
    void parseChannelPls(Channel* channel);
    virtual void parseAfter();
    void duplicateGenre();
    void duplicateGenre(const QModelIndex &index);
    void calculMaximumListeners();
};

#endif // CHANNELSMODEL_H
