#ifndef CHANNELSONGSMODEL_H
#define CHANNELSONGSMODEL_H

#include "xmlModel.h"

class ChannelSong;

class ChannelSongsModel : public XmlModel
{
    Q_OBJECT
public:
    explicit ChannelSongsModel(QObject *parent = 0);
    ~ChannelSongsModel();
    Q_INVOKABLE void setChannelId(QString channelId);

private:
    virtual XmlItem* parseXmlItem();
};

#endif // CHANNELSONGSMODEL_H
