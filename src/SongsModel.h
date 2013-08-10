#ifndef SONGSMODEL_H
#define SONGSMODEL_H

#include "XmlModel.h"

class Song;

class SongsModel : public XmlModel
{
    Q_OBJECT
public:
    explicit SongsModel(QObject *parent = 0);
    ~SongsModel();
    Q_INVOKABLE void setChannelId(QString channelId);

private:
    virtual XmlItem* parseXmlItem();

private:
    QString m_channelId;
};

#endif // SONGSMODEL_H
