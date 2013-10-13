#ifndef SONGSMODEL_H
#define SONGSMODEL_H

#include "../XmlItem/XmlItemModel.h"

class Song;
class Channel;

class SongsModel : public XmlItemModel
{
    static const QUrl _channelSongsUrl;

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
