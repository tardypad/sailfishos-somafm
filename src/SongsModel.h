#ifndef SONGSMODEL_H
#define SONGSMODEL_H

#include "XmlModel.h"

class Song;
class Channel;

class SongsModel : public XmlModel
{
    Q_OBJECT
public:
    explicit SongsModel(QObject *parent = 0);
    ~SongsModel();
    Q_INVOKABLE void setChannel(XmlItem* channel);

private:
    virtual bool stopParsing(XmlItem *xmlItem);
    virtual XmlItem* parseXmlItem();

private:
    Channel* m_channel;
};

#endif // SONGSMODEL_H
